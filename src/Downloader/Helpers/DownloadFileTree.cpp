#include "DownloadFileTree.hpp"

void DownloadFileTree::add(const std::unique_ptr<Reference>& ref, bool isLocked, bool isDownloaded) {
  try {
    logTreeDescription();
    auto tmp = root;
    search(tmp, ref, true);

    if (tmp != root) {
      tmp -> state.isLocked = isLocked;
      tmp -> state.isDownloaded = isDownloaded;
    }
  } catch (const LockedReferenceException& exc) {
    std::cout << exc.what() << std::endl;
  } catch (const OutOfMaximalDepthException& exc) {
    std::cout << exc.what() << std::endl;
  }
}

void DownloadFileTree::setDownloaded(const std::unique_ptr<Reference>& ref) {
  auto tmp = root;
  find(tmp, ref);
  if (tmp != root)
    tmp -> state.isDownloaded = true;
}

void DownloadFileTree::setLocked(const std::unique_ptr<Reference>& ref) {
  auto tmp = root;
  find(tmp, ref);
  if (tmp != root)
    tmp -> state.isDownloaded = true;
}

void DownloadFileTree::setFailed(const std::unique_ptr<Reference>& ref) {
  auto tmp = root;
  find(tmp, ref);
  if (tmp != root)
    tmp -> state.isDownloaded = true;
}

std::string DownloadFileTree::nextDownloadReference() const {
  switch (traverseStyle) {
  case TraverseStyle::BREADTH_FIRST_SEARCH:
    break;
  case TraverseStyle::DEPTH_FIRST_SEARCH:
    break;
  }

  return "";
}

void DownloadFileTree::logTreeDescription() const {
  logTreeDescription(root, 0);
}

void DownloadFileTree::logTreeDescription(const std::shared_ptr<Node>& node, int level) const {
  std::cout << std::string(level * 2, ' ') << node -> name << "[LOCKED]" << node -> state.isLocked << std::endl;

  for (const auto& ref: node -> children)
    if (ref -> isLeaf)
      std::cout << std::string(level * 2, ' ') << ref -> name << " [LEAF] " << std::endl;
    else
      logTreeDescription(ref, level + 1);
}

void DownloadFileTree::addNewNode(std::shared_ptr<Node>& parent, const std::string& name, bool isLeaf) {
  std::shared_ptr<Node> newNode = std::make_shared<Node>(name);
  newNode -> isLeaf = isLeaf;
  parent -> children.push_back(newNode);
  parent = newNode;
}

void DownloadFileTree::find(std::shared_ptr<Node>& node, const std::unique_ptr<Reference>& ref) {
  try {
    auto tmp = root;
    search(tmp, ref, false);

    if (tmp != root && tmp -> isLeaf)
      node = tmp;
    else
      throw Exception("Reference doesn't points to the file");

  } catch (const LockedReferenceException& exc) {
    std::cout << exc.what() << std::endl;
  }
}

void DownloadFileTree::search(std::shared_ptr<Node>& node, const std::unique_ptr<Reference>& ref, bool insertItemsDuringSearch) {
  if (!ref -> isRelative())
    throw Exception("Can't work with not relative directory");

  Data<> path(ref -> getPath());
  std::string separator = "/";

  uint8_t depth = 0;

  while (true) {
    if (depth > this -> depth)
      throw OutOfMaximalDepthException(this -> depth);

    auto begin = path.at(1), separatorIndex = path.find(separator, begin);
    Data<> component = path.subsequence(begin, separatorIndex);
    bool isLeaf = separatorIndex == path.end();

    if (separatorIndex != path.end())
      std::advance(separatorIndex, 1);
    path.eraseSequence(begin, separatorIndex);

    std::string name = component.stringRepresentation();

    if (name.empty())
      break;

   if (node -> state.isLocked) {
      node = root;
      throw LockedReferenceException();
    }

    auto index = node -> find(name, isLeaf);

    if (index == node -> children.end()) {
      if (insertItemsDuringSearch) {
        addNewNode(node, name, isLeaf);
        depth++;
        continue;
      }

      node = root;
      return;
    }

    node = *index;
    depth++;

    if (node -> isLeaf)
      return;
  }
}

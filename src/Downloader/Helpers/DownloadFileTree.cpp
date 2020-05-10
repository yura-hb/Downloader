#include "DownloadFileTree.hpp"

void DownloadFileTree::add(const std::unique_ptr<Reference>& ref, bool isLocked, bool isDownloaded) {
  try {
    auto tmp = root;
    search(tmp, ref, true);

    tmp -> state.isLocked = isLocked;
    tmp -> state.isDownloaded = isDownloaded;
  } catch (const LockedReferenceException& exc) {
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

  auto prev = path.find(separator, path.begin(), true);
  auto next = prev;

  while ((next = path.find(separator, next)) != path.end()) {
    Data<> component = path.subsequence(prev, next);
    std::string name = component.stringRepresentation();

    std::advance(next, separator.size());
    prev = next;

    auto index = node -> find(name, false);

    if (index == node -> children.end()) {

      if (insertItemsDuringSearch) {
        addNewNode(node, name, false);
        continue;
      }

      node = root;
      return;
    }

    if (node -> state.isLocked) {
      node = root;
      throw LockedReferenceException();
    }

    node = *index;
  }
  Data<> filename = path.subsequence(prev, next);
  std::string name = filename.stringRepresentation();

  if (name.empty())
    return;

  auto index = node -> find(name, false);

  if (index == node -> children.end())
    if (insertItemsDuringSearch)
      addNewNode(node, name, true);
    else
      node = root;
  else
    node = *index;
}

#include "DownloadFileTree.hpp"

void DownloadFileTree::add(const Reference& ref, bool isLocked, bool isDownloaded) {
  try {
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

void DownloadFileTree::setDownloaded(const Reference& ref) {
  auto tmp = root;
  find(tmp, ref);
  std::cout << "Set downloaded" << tmp -> name << ref.getPath() << std::endl;
  if (tmp != root)
    tmp -> state.isDownloaded = true;
}

void DownloadFileTree::setLocked(const Reference& ref) {
  auto tmp = root;
  find(tmp, ref);
  if (tmp != root)
    tmp -> state.isDownloaded = true;
}

void DownloadFileTree::setFailed(const Reference& ref) {
  auto tmp = root;
  find(tmp, ref);
  if (tmp != root)
    tmp -> state.isDownloaded = true;
}

std::string DownloadFileTree::nextDownloadReference() const {
  std::shared_ptr<Node> node;

  std::function<bool(const std::shared_ptr<Node>)> predicate = [](const std::shared_ptr<Node>& node) {
    return node -> isDownloadable();
  };

  switch (traverseStyle) {
  case TraverseStyle::BREADTH_FIRST_SEARCH:
    node = breadthFirstSearch(predicate);
    break;
  case TraverseStyle::DEPTH_FIRST_SEARCH:
    node = depthFirstSearch(predicate);
    break;
  }

  if (node == root)
    return "";

  std::string path = "";

  std::weak_ptr<Node> tmp = node;

  while (true) {
    auto nodeValue = tmp.lock();

    if (!nodeValue || nodeValue == root)
      break;

    path = "/" + nodeValue -> name + path;
    tmp = nodeValue -> parent;
  }

  return path;
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

  std::weak_ptr<Node> weakParent = parent;
  newNode -> parent = weakParent;

  parent -> children.push_back(newNode);
  parent = newNode;
}

void DownloadFileTree::find(std::shared_ptr<Node>& node, const Reference& ref) {
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

void DownloadFileTree::search(std::shared_ptr<Node>& node, const Reference& ref, bool insertItemsDuringSearch) {
  if (!ref.isRelative())
    throw Exception("Can't work with not relative directory");

  Data<> path(ref.getPath());
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

std::shared_ptr<DownloadFileTree::Node> DownloadFileTree::breadthFirstSearch(std::function<bool(const std::shared_ptr<Node>)>& predicate) const {
  std::queue<std::shared_ptr<Node>> queue;

  queue.push(root);

  while (!queue.empty()) {
    std::shared_ptr<Node> node = queue.front();
    queue.pop();

    if (predicate(node))
      return node;

    for (const auto& child: node -> children)
      queue.push(child);
  }

  return root;
}

std::shared_ptr<DownloadFileTree::Node> DownloadFileTree::depthFirstSearch(std::function<bool(const std::shared_ptr<Node>)>& predicate) const {
  std::stack<std::shared_ptr<Node>> stack;

  stack.push(root);

  while (!stack.empty()) {
    std::shared_ptr<Node> node = stack.top();
    stack.pop();

    if (predicate(node))
      return node;

    for (const auto& child: node -> children)
      stack.push(child);
  }

  return root;
}

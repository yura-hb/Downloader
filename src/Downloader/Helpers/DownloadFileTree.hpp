#ifndef __FILE_TREE__
#define __FILE_TREE__

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <queue>

#include "../../FileManager/Models/Reference.hpp"
#include "../../Base/Data.hpp"

/**
 *  @brief
 *    Help class to store locked and downloaded file references in the tree format.
 *
 *    Each node can be either be path component or the "/" separator. The leaf of the tree is the Node,
 *    which has the isLeaf flag set. The tree separate tree nodes and the directory nodes, as they can have the same filename.
 */
struct DownloadFileTree {
  public:
    enum class TraverseStyle {
      BREADTH_FIRST_SEARCH,
      DEPTH_FIRST_SEARCH
    };
    /**
     * @brief
     *   Initiates the download tree.
     *
     * Input:
     *   - @param[in] depth - maximal depth from the root of the tree. (The root of the tree is /)
     *   - @param[in] traverseStyle - the style of traversal
     */
    DownloadFileTree(const uint8_t& depth, const TraverseStyle& traverseStyle): depth(depth), traverseStyle(traverseStyle) {
      root = std::make_unique<Node>("/");
    }
    /**
     *  @brief
     *    Adds the element to the tree.
     *
     *  Input:
     *    @param[in] ref - reference, containing the relative path from the current directory
     *    @param[in] isLocked - boolean flag indicating, that the element is locked
     *    @param[in] isDownloaded - boolead flag indicating, that the element is downloaded
     *
     *  Throws:
     *    Throws an exception, in case, if is the reference is not relative.
     *
     */
    void add(const Reference& ref, bool isLocked = false, bool isDownloaded = false);
    /**
     *  @brief
     *    Sets the download flag on the element at the specific reference
     *
     *  Input:
     *    @param[in] ref - reference, containing the relative path from the current directory
     *
     *  Throws:
     *    Throws an exception, in case, if the reference doesn't points to the file.
     *
     */
    void setDownloaded(const Reference& ref);
    /**
     *  @brief
     *    Sets the locked flag at the specific file path
     *
     *  Input:
     *    @param[in] ref - reference, containing the relative path from the current directory
     *
     *  Throws:
     *    Throws an exception, in case, if the reference doesn't points to the file.
     *
     */
    void setLocked(const Reference& ref);
    /**
     *  @brief
     *    Sets the locked flag at the specific file path
     *
     *  Input:
     *    @param[in] ref - reference, containing the relative path from the current directory
     *
     *  Throws:
     *    Throws an exception, in case, if the reference doesn't points to the file.
     *
     */
    void setFailed(const Reference& ref);
    /**
     *  @brief
     *    Recursively traverses download tree, depending on the style and returns the relative path on the server.
     *
     *  Output:
     *    - @param[out] - string path to the file, in case, if some finded, otherwise empty string.
     */
    std::string nextDownloadReference() const;
    /**
     *  @brief
     *    Prints out the state of the tree and each node
     */
    void logTreeDescription() const;
  private:
    class LockedReferenceException: public std::exception {
      public:
        const char * what() const noexcept {
          return "The reference is locked, can't continue";
        }
    };
    class OutOfMaximalDepthException: public std::exception {
      public:
        OutOfMaximalDepthException(const uint8_t& maximalDepth) {
          description = "The item is out of the maximal depth, can't add";
          description += " [ Limit: " + std::to_string(maximalDepth) + " ]";
        }

        const char * what() const noexcept {
          return description.c_str();
        }
      private:
        std::string description;
    };
    struct Node {
      struct State {
        /**
         *  @brief
         *    Validates if the file is downloaded, so the true statement is equivalent to that the
         *    element is a file. However, it is not equivalent to the
         */
        bool isDownloaded = false;
        /**
         *  @brief
         *    Validates if the directory is locked, so the directory can't have any child, under that path.
         */
        bool isLocked = false;
        /**
         *  @brief
         *    Validates if the directory is failed, so the directory can't have any child, under that path.
         */
        bool isFailed = false;
      };

      std::string name;
      bool isLeaf = false;
      std::vector<std::shared_ptr<Node>> children;
      std::weak_ptr<Node> parent;
      State state;

      Node(const std::string& str): name(str) {}
      /**
       *  @brief
       *    Finds children in the current node by the name and type of the node.
       *
       *  Input:
       *    - @param[in] name - name of the node to add
       *    - @param[in] isLeaf - flag indicating, that the element is leaf or not
       *
       */
      std::vector<std::shared_ptr<Node>>::iterator find(const std::string& name, bool isLeaf) {
        return std::find_if(children.begin(), children.end(), [&](const std::shared_ptr<Node>& node) {
          return node -> name == name && node -> isLeaf == isLeaf;
        });
      }
    };

    const uint8_t depth;
    const TraverseStyle traverseStyle;
    std::shared_ptr<Node> root;
    /**
     *  Input:
     *    - @param[in] parent - node, to which the new element is added.
     *    - @param[in] name - name of the new node.
     *    - @param[in] isLeaf - flag indicating, that the element is leaf or not.
     */
    void addNewNode(std::shared_ptr<Node>& parent, const std::string& name, bool isLeaf);
    /**
     *  Input:
     *    - @param[in] node - node, from which the search begins.
     *    - @param[in] ref - relative reference to some element.
     */
    void find(std::shared_ptr<Node>& node, const Reference& ref);
    /**
     *  @brief
     *    Searches the element in the tree and sets the reference on the some Node.
     *    Ends searching, in case if some reference is locked.
     *
     *  Input:
     *    - @param[in] node - node, from which the search begins.
     *    - @param[in] ref - relative reference to some element.
     *    - @param[in] insertItemsDuringSearch - flag, indicating, if the should add new elements during the search
     *
     *  Output:
     *    - @param[out] node - current node, where the search ends, in case of error, returns refernce to the root element.
     *
     *  Throws:
     *    - In case, if the reference if not the relative
     *    - In case, if the reference is locked
     *
     */
    void search(std::shared_ptr<Node>& node, const Reference& ref, bool insertItemsDuringSearch);
    /**
     *  Input:
     *    - @param[in] node - node, from which start printing.
     *    - @param[in] level - level of printing the node.
     */
    void logTreeDescription(const std::shared_ptr<Node>& node, int level = 0) const;

    std::string breadthFirstSearch() const;

    std::string depthFirstSearch() const;
};

#endif

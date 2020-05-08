#include "PageMirrorer.hpp"

void PageMirrorer::mirror(const RemoteReference& ref, const LocalReference& filepath) const {


}

void PageMirrorer::download(const RemoteReference& ref, const LocalReference& filepath) const {
  Downloader::download(ref, filepath);
  // - TODO: - Add analyzer
}

bool prepare(const RemoteReference& url) {

}

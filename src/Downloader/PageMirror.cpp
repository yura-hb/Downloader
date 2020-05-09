#include "PageMirror.hpp"

void PageMirror::mirror(const RemoteReference& ref, const LocalReference& filepath) const {


}

void PageMirror::download(const RemoteReference& ref, const LocalReference& filepath) const {
  FileDownloader::download(ref, filepath);
  // - TODO: - Add analyzer
}

bool PageMirror::prepare(const RemoteReference& url) {

}

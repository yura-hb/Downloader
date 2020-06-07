#include "ArgumentParser.hpp"

int ArgumentParser::handle(int argc, char * argv[]) {
  std::cout << argc << std::endl;
  if (argc == 1) {
    notifyError();
    return 0;
  }

  std::string link;
  std::map<std::string, bool> arguments = {};
  size_t depth = -1;

  int result = 0;

  if ((result = processArguments(argc, argv, arguments, link, depth)) || (result = handleArguments(arguments, link, depth)))
    return result;

  return 0;
}

int ArgumentParser::handleArguments(const std::map<std::string, bool>& arguments, const std::string& link, const size_t& depth) {

  if (arguments.at("-h")) {
    showUserHelpMessage();
    return 0;
  }

  URL url(link);

  if (!url.isValid()) {
    std::cout << "Incorrect url" << std::endl;
    notifyError();
    return 1;
  }

  Configuration::shared.overrideReferences = arguments.at("-o");
  Configuration::shared.removedOriginFiles = !arguments.at("-O");
  Configuration::shared.fixHtmlPathes = arguments.at("-x");

  RemoteReference ref(url);

  if (arguments.at("-r")) {
    bool isBreadthFirstSearch = !arguments.at("-D");

    PageMirror downloader(
      depth,
      isBreadthFirstSearch ? DownloadFileTree::TraverseStyle::BREADTH_FIRST_SEARCH : DownloadFileTree::TraverseStyle::DEPTH_FIRST_SEARCH
    );

    downloader.mirror(ref);
  } else {
    FileDownloader downloader;

    std::string filename = "index.html";

    if (!ref.isDirectory())
      filename = ref.filename();

    downloader.download(ref, LocalReference(filename));
  }

  return 0;
}

int ArgumentParser::processArguments(int argc, char *argv[], std::map<std::string, bool>& arguments, std::string& link, size_t& depth) {
  arguments.insert(std::make_pair("-h", false));
  arguments.insert(std::make_pair("-l", false));
  arguments.insert(std::make_pair("-r", false));
  arguments.insert(std::make_pair("-o", false));
  arguments.insert(std::make_pair("-O", false));
  arguments.insert(std::make_pair("-B", false));
  arguments.insert(std::make_pair("-D", false));
  arguments.insert(std::make_pair("-x", false));
  arguments.insert(std::make_pair("-d", false));

  bool waitForLink = false, waitForDepth = false;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (waitForLink) {
      link = arg;
      waitForLink = false;
      continue;
    }

    if (waitForDepth) {
      try {
        depth = std::stoul(arg, nullptr, 0);
      } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
      }
      waitForDepth = false;
      continue;
    }

    if (arg.size() && arg[0] == '-') {
      if (arg == "-l") {
        waitForLink = true;
        continue;
      }

      if (arg == "-d") {
        waitForDepth = true;
        continue;
      }

      for (size_t i = 1; i < arg.size(); i++) {
        std::string simpleArg(1, arg[i]);
        simpleArg.insert(0, "-");

        if (arguments.find(simpleArg) != arguments.end()) {

          if (simpleArg == "-l" || simpleArg == "-d") {
            std::cout << "Argument" << " " << simpleArg << " can't be merged in other arguments" << std::endl;
            notifyError();
            return 1;
          }

          arguments[simpleArg] = true;
        }
      }
    }
  }

  return 0;
}

void ArgumentParser::notifyError() {
  std::cout << "Missing link..." << std::endl;
  std::cout << "Usage: [[PROGRAM]] .. [[OPTIONS]] ... -l [[LINK]]" << std::endl << std::endl;

  std::cout << "If you need to get help" << std::endl;
  std::cout << "Print: [[PROGRAM]] -h" << std::endl;
}

void ArgumentParser::showUserHelpMessage() {
  std::cout << "Arguments: (Should be written in the separated form -h -r -o -O)" << std::endl;

  std::cout << std::setw(4) << "-h " << std::setfill(' ') << "Print help." << std::endl;
  std::cout << std::setw(4) << "-l " << std::setfill(' ') << "The link to download file from. In format -l [LINK]" << std::endl;
  std::cout << std::setw(4) << "-r " << std::setfill(' ') << "Set recursive download for the link." << std::endl;
  std::cout << std::setw(4) << "-d " << std::setfill(' ') << "Depth from the root directory of the server. Root is zero, default infinity (Work only with -r flag the enabled)" << std::endl;
  std::cout << std::setw(4) << "-o " << std::setfill(' ') << "Overwrite downloaded files to the local directories. (Work only with -r flag enabled)" << std::endl;
  std::cout << std::setw(4) << "-O " << std::setfill(' ') << "Leave the originally downloaded files. (Work only with -r flag enabled)" << std::endl;
  std::cout << std::setw(4) << "-x " << std::setfill(' ') << "Fix HTML files by adding the file suffix .html for the text/html files (Work only with -ro flags enabled)" << std::endl;
  std::cout << std::setw(4) << "-B " << std::setfill(' ') << "Perform breadth-first stepping during the file downloading. (Default) (Work only with -r flag enabled)" << std::endl;
  std::cout << std::setw(4) << "-D " << std::setfill(' ') << "Perform deapth-first stepping during the file downloading. (Work only with -r flag enabled)" << std::endl;
}

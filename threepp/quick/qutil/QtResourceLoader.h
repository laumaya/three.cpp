//
// Created by byter on 2/11/18.
//

#ifndef THREE_PP_QTRESOURCELOADER_H
#define THREE_PP_QTRESOURCELOADER_H

#include <QThread>
#include <QFile>
#include <string>
#include <unordered_map>
#include <threepp/loader/Loader.h>

namespace three {
namespace quick {

/**
 * loader that resolves resources from Qt resource storage
 */
class QtResourceLoader : public QThread, public three::ResourceLoader
{
  Q_OBJECT

  three::Loader &loader;
  QFile file;

  std::unordered_map<std::string, std::string> _replacements;

protected:
  void run() override;

public:
  QtResourceLoader(three::Loader &assimp, const QString &url, const std::unordered_map<std::string, std::string> &replacements);

  bool exists(const char *path) override;

  three::Resource::Ptr get(const char *path, std::ios_base::openmode openmode) override;

  void load(QImage &image, std::string &file) override;

signals:
  void loaded();
};

}
}

#endif //THREE_PP_QTRESOURCELOADER_H

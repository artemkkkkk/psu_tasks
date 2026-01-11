#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <vector>
#include <string>

/**
 * Сохраняет магический квадрат в текстовый файл с выравниванием.
 * @param square Квадрат для сохранения.
 * @param filename Имя файла.
 * @return true при успехе, false при ошибке записи.
 */
bool SaveSquareToFile(const std::vector<std::vector<int>>& square,
                      const std::string& filename);

#endif // FILE_IO_H_
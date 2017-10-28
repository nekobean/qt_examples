# CMake の最低限必要なバージョンは設定する。
# Qt では 2.8.3 以上が必須、3.1.0 以上が推奨である。
cmake_minimum_required(VERSION 2.8.3)

# プロジェクト名を設定する。
project(sample)

# ビルドディレクトリを include ディレクトリに追加するオプションを有効にする。
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# MOC が必要な場合は有効にするオプションを有効にする。
set(CMAKE_AUTOMOC ON)

# QtWidgets ライブラリを検索する。
find_package(Qt5Core REQUIRED)

# src ディレクトリにあるビルド対象のファイルをリストアップする。
file(GLOB_RECURSE CPP_FILES src/*.cpp)

# src ディレクトリを include ディレクトリに追加する。
include_directories(src)

# 生成する実行ファイルを追加する。
add_executable(${PROJECT_NAME}
    ${CPP_FILES}
)

# 依存ライブラリをリンクする。
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
)

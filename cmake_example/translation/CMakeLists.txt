# CMake の最低限必要なバージョンは設定する。
# Qt では 2.8.3 以上が必須、3.1.0 以上が推奨である。
cmake_minimum_required(VERSION 2.8.3)

# プロジェクト名を設定する。
project(sample)

# ビルドディレクトリを include ディレクトリに追加するオプションを有効にする。
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# MOC が必要な場合は自動的に実行するオプションを有効にする。
set(CMAKE_AUTOMOC ON)

# UI 定義ファイルの変換が必要な場合は自動的に実行するオプションを有効にする。
set(CMAKE_AUTOUIC ON)

# QtWidgets ライブラリを追加する。
find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)

# src ディレクトリにあるビルド対象のファイルをリストアップする。
file(GLOB_RECURSE CPP_FILES src/*.cpp)
file(GLOB_RECURSE UI_FILES src/*.ui)

# 生成する翻訳スクリプトファイルを設定する。
SET(TS_FILES
    lang/japanese.ts
)

# 翻訳対象のファイルを設定する。
SET(TRANSLATION_TARGET_FILES
    ${CPP_FILES}
    ${UI_FILES}
)

# 翻訳ファイルを生成する設定を行う。
qt5_create_translation(QM_FILES
    ${TRANSLATION_TARGET_FILES} # 翻訳対象のファイル
    ${TS_FILES}                 # 翻訳スクリプトファイル
)

# src ディレクトリを include ディレクトリに追加する。
include_directories(src)

# 生成する実行ファイルを追加する
add_executable(${PROJECT_NAME}
    ${CPP_FILES}
    ${UI_FILES}
    ${QM_FILES}
)

# 依存ライブラリをリンクする
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
)

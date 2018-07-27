#include "myopenglwidget.h"

#include <iostream>

#include <QFile>
#include <QTextStream>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

MyOpenGLWidget::~MyOpenGLWidget()
{
}

/**
 * @brief 初期化処理を記述する。
 */
void MyOpenGLWidget::initializeGL()
{
    // OpenGL の API を呼ぶ前に呼ぶ。
    initializeOpenGLFunctions();

    // シェーダーのコードを読み込む。
    GLuint vertexShaderHandle =
        createShaderFromFile(GL_VERTEX_SHADER, ":/vertex.glsl");
    GLuint fragmentShaderHandle =
        createShaderFromFile(GL_FRAGMENT_SHADER, ":/fragment.glsl");

    // プログラムオブジェクトを作成する。
    programHandle_ = glCreateProgram();
    if (programHandle_ == 0) {
        std::cerr << "failed to create the program object." << std::endl;
        exit(1);
    }

    // プログラムオブジェクトに頂点シェーダーオブジェクトを追加する。
    glAttachShader(programHandle_, vertexShaderHandle);
    // プログラムオブジェクトにフラグメントシェーダーオブジェクトを追加する。
    glAttachShader(programHandle_, fragmentShaderHandle);

    // プログラムオブジェクトをリンクする。
    glLinkProgram(programHandle_);

    // リンクに成功したかどうかを取得する。
    GLint status;
    glGetProgramiv(programHandle_, GL_LINK_STATUS, &status);

    // リンクに失敗した場合
    if (status == GL_FALSE) {
        std::cerr << "Failed to link the program." << std::endl;

        // ログのある場合、文字列の長さを取得する。
        GLint logLen;
        glGetProgramiv(programHandle_, GL_INFO_LOG_LENGTH, &logLen);

        // ログがある場合
        if (logLen > 0) {
            // ログを格納するバッファを作成する。
            char *log = new char[logLen];
            glGetProgramInfoLog(programHandle_, logLen, NULL, log);

            // ログを取得し、表示する。
            std::cerr << log << std::endl;

            // ログを格納するバッファを削除する。
            delete log;
        }
        exit(1);
    }

    // プログラムオブジェクトをインストールする。
    glUseProgram(programHandle_);
}

/**
 * @brief リサイズされた際の処理を記述する。
 */
void MyOpenGLWidget::resizeGL(int width, int height){}

;
/**
 * @brief 描画する際の処理を記述する。
 */
void MyOpenGLWidget::paintGL()
{
}

#include <iostream>

/**
 * @brief ファイルからソースコードを読み込み、シェーダーをコンパイルする。
 * @param shaderType シェーダーの種類
 * @param source ソースコード
 * @return シェーダーオブジェクトのハンドラ
 */
GLuint
MyOpenGLWidget::createShaderFromFile(GLenum shaderType, const QString &filePath)
{
    // ファイルを開く。
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        exit(1);

    // ファイルからソースコードを読み込む。
    QTextStream in(&file);
    QString source = in.readAll();

    return createShaderFromString(shaderType, source);
}

/**
 * @brief ソースコードからシェーダーをコンパイルする。
 * @param shaderType シェーダーの種類
 * @param source ソースコード
 * @return シェーダーオブジェクトのハンドラ
 */
GLuint
MyOpenGLWidget::createShaderFromString(GLenum shaderType, const QString &source)
{
    // シェーダーオブジェクトを作成する。
    GLuint shaderHandle = glCreateShader(shaderType);
    if (shaderHandle == 0) {
        std::cerr << "failed to create the shader object." << std::endl;
        exit(1);
    }

    // シェーダーオブジェクトにソースコードを設定する。
    const GLchar *sources[] = {qPrintable(source)};
    glShaderSource(shaderHandle, 1, sources, NULL);

    // ソースコードをコンパイルする。
    glCompileShader(shaderHandle);

    // コンパイルに成功したかどうかを取得する。
    GLint result;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);

    // コンパイルに失敗した場合
    if (result == GL_FALSE) {
        std::cerr << "failed to compile the shader object." << std::endl;

        // ログの長さを取得する。
        GLint logLen;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLen);

        // ログがある場合
        if (logLen > 0) {
            // ログを取得し、表示する。
            char *log = new char[logLen];
            glGetShaderInfoLog(shaderHandle, logLen, NULL, log);
            std::cout << log << std::endl;
            delete log;
        }
        exit(1);
    }

    return shaderHandle;
}

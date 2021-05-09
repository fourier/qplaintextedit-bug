#include <QApplication>
#include <QPlainTextEdit>
#include <QString>
#include <QtDebug>
#include <QTimer>
#include <QDesktopServices>

class MainWindow : public QPlainTextEdit
{
public:
    MainWindow(QWidget *parent) : QPlainTextEdit(parent)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(2000);
    }

    ~MainWindow() { timer->stop(); }

    void update() { appendPlainText("some more text from timer\n"); }

private:
    QTimer *timer;
    QString clickedAnchor;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.appendPlainText("Hello QPlainTextEdit\n");
    w.appendHtml("<a href=\"https://doc.qt.io/qt-5/qplaintextedit.html\">QPlainTextEdit</a>\n");
    w.appendPlainText("Normal text\n");
    w.show();

    return a.exec();
}

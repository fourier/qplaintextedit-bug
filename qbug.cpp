#include <QApplication>
#include <QPlainTextEdit>
#include <QString>
#include <QtDebug>
#include <QTimer>
#include <QDesktopServices>
#include <QTextCursor>
#include <QTextCharFormat>

class MainWindow : public QPlainTextEdit
{
public:
    MainWindow(QWidget *parent) : QPlainTextEdit(parent)
    {
        this->setMouseTracking(true);
        this->setFocusPolicy(Qt::NoFocus);
        this->setReadOnly(true);
        this->setUndoRedoEnabled(false);

        setMaximumBlockCount(0);
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(2000);
    }

    ~MainWindow() { timer->stop(); }

    void insertLink()
    {
        // w.appendHtml("<a
        // href=\"https://doc.qt.io/qt-5/qplaintextedit.html\">QPlainTextEdit</a>\n");
        QTextCursor cursor = textCursor();
        normalFmt = cursor.charFormat();
        // cursor.insertHtml("<a
        // href=\"https://doc.qt.io/qt-5/qplaintextedit.html\">QPlainTextEdit</a>\n");
        QTextCharFormat fmt;
        fmt.setAnchor(true);
        // QStringList  names;
        // names << "doc";
        // fmt.setAnchorNames(names);
        fmt.setAnchorHref("https://doc.qt.io");
        cursor.insertText("this is a link", fmt);
        cursor.insertText("\n", normalFmt);
    }
    void update() {
        appendPlainText("some more text from timer\n");
    }

    void mousePressEvent(QMouseEvent *e)
    {
        // clickedAnchor = (e->button() == Qt::LeftButton) ? anchorAt(e->pos()) : QString();
        //QPlainTextEdit::mousePressEvent(e);
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        // if (e->button() == Qt::LeftButton && !clickedAnchor.isEmpty()) {
        //     if (anchorAt(e->pos()) == clickedAnchor) {
        //         QDesktopServices::openUrl(QUrl(clickedAnchor, QUrl::TolerantMode));
        //         qDebug() << "CLICKED: " << clickedAnchor;
        //     }
        //     clickedAnchor.clear();
        // }
        // QPlainTextEdit::mouseReleaseEvent(e);
        // textCursor().setCharFormat(normalFmt);
    }

    void mouseMoveEvent(QMouseEvent *e)
    {
        qDebug() << "mouseMoveEvent: " << e->pos();
        if (!anchorAt(e->pos()).isEmpty()) {
            qDebug() << " anchor: " << anchorAt(e->pos()) << " clickedAnchor: " << clickedAnchor;
            viewport()->setCursor(Qt::PointingHandCursor);
        } else {
            qDebug() << " no anchor";
            viewport()->unsetCursor();
        }
        QPlainTextEdit::mouseMoveEvent(e);
    }

private:
    QTimer *timer;
    QString clickedAnchor;
    QTextCharFormat normalFmt;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.appendPlainText("Hello QPlainTextEdit\n");
    // w.appendHtml("<a href=\"https://doc.qt.io/qt-5/qplaintextedit.html\">QPlainTextEdit</a>\n");
    w.insertLink();
    w.appendPlainText("Normal text\n");
    w.show();

    return a.exec();
}

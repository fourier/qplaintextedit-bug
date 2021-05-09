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
        this->setFocusPolicy(Qt::NoFocus);
        this->setReadOnly(true);
        this->setUndoRedoEnabled(false);
        this->setMouseTracking(true);

        QPalette p = viewport()->palette();
        p.setColor(QPalette::Text, QColor("#a9b7c6"));
        p.setColor(QPalette::Base, QColor("#2b2b2b"));
        setPalette(p);
        this->document()->setMaximumBlockCount(2000);
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(2000);
    }

    ~MainWindow() { timer->stop(); }

    void update() { appendPlainText("some more text from timer\n"); }

    void mousePressEvent(QMouseEvent *e)
    {
        clickedAnchor = (e->button() == Qt::LeftButton) ? anchorAt(e->pos()) : QString();
        QPlainTextEdit::mousePressEvent(e);
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton && !clickedAnchor.isEmpty()) {
            if (anchorAt(e->pos()) == clickedAnchor) {
                QDesktopServices::openUrl(QUrl(clickedAnchor, QUrl::TolerantMode));
                qDebug() << "CLICKED: " << clickedAnchor;
            }
            clickedAnchor.clear();
        }
        QPlainTextEdit::mouseReleaseEvent(e);
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

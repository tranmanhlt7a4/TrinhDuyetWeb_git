#ifndef TRINHDUYET_H
#define TRINHDUYET_H

#ifndef CUASOTRINHDUYET_H
#define CUASOTRINHDUYET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QMainWindow>
#include <QAction>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QMenu>
#include <QList>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QString>
#include <QtWebEngineWidgets>

class TrinhDuyet : public QMainWindow
{
    Q_OBJECT

public:
    TrinhDuyet();

private:
    void khoiTaoGiaoDien();
    void khoiTaoThanhDanhMuc();
    void khoiTaoToolBar();
    void khoiTaoStatusBar();
    QWebEngineView* trangHienTai();
    QWidget* taoTabMoi();

private slots:
    void taiTrangWeb(QString url);
    void thaoTacTaiTrang();
    void thaoTacDungTai();
    void thaoTacTrangTruoc();
    void thaoTacTrangSau();
    void thaoTacTrangChu();
    void thaoTacTabMoi();
    void thaoTacXoaTab();
    void anEnterThanhDiaChi();
    void anNutDi();
    void thayDoiTab();
    void batDauTienTrinh();
    void tienTrinh(int tienTrinhDaTai);
    void taiXong();
    void thayDoiTieuDe(QString tieuDe);
    void thayDoiURL(QUrl url);
    void thongTin();

private:
    QAction *m_taiTrang;
    QAction *m_trangTruoc;
    QAction *m_trangSau;
    QAction *m_dungTai;
    QAction *m_trangChu;
    QAction *m_tabMoi;
    QAction *m_xoaTab;
    QList<QAction *> cacThaoTac;

    QLineEdit *m_thanhDiaChi;
    QPushButton *m_nutDi;

    QTabWidget *m_cacTheTrang;

    QProgressBar *m_tienTrinhTaiTrang;

};

#endif // CUASOTRINHDUYET_H


#endif // TRINHDUYET_H

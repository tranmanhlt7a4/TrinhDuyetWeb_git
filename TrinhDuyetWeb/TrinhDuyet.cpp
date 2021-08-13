#include "TrinhDuyet.h"

TrinhDuyet::TrinhDuyet()
{
    khoiTaoGiaoDien();
    khoiTaoThanhDanhMuc();
    khoiTaoToolBar();
    khoiTaoStatusBar();

    setMinimumSize(1080, 500);
    setWindowIcon(QIcon("D:/Code/icon/Browser.png"));
    setWindowTitle(tr("Trình duyệt web"));
}

void TrinhDuyet::khoiTaoGiaoDien(){
    //tao cac tab
    m_cacTheTrang = new QTabWidget();

    //nut them tab
    QPushButton *nutThemTab = new QPushButton(tr(""));
        nutThemTab->setIcon(QIcon("D:/Code/icon/Tabmoi.png"));

    m_cacTheTrang->setCornerWidget(nutThemTab);

    thaoTacTabMoi();

    setCentralWidget(m_cacTheTrang);

    connect(nutThemTab, SIGNAL(clicked()), this, SLOT(thaoTacTabMoi()));
    connect(m_cacTheTrang, SIGNAL(currentChanged(int)), this, SLOT(thayDoiTab()));

}

void TrinhDuyet::khoiTaoThanhDanhMuc(){
    QMenu *menuChucNang = menuBar()->addMenu(tr("Chức năng trình duyệt"));

    m_taiTrang = new QAction(QIcon("D:/Code/icon/Tailai.png"), tr("Tải lại trang"));
    m_dungTai = new QAction(QIcon("D:/Code/icon/Dungtai.png"), tr("Dừng tải trang"));
        m_dungTai->setVisible(false);
    m_trangChu = new QAction(QIcon("D:/Code/icon/Homepage.png"), tr("Trang chủ"));
    m_trangTruoc = new QAction(QIcon("D:/Code/icon/Trangtruoc.png"), tr("Trang trước"));
        m_trangTruoc->setToolTip(tr("Trở về trang trước đó"));
    m_trangSau = new QAction(QIcon("D:/Code/icon/Trangsau.png"), tr("Trang sau"));
        m_trangSau->setToolTip(tr("Trở về trang sau"));
    m_tabMoi = new QAction(QIcon("D:/Code/icon/Tabmoi.png"), tr("Tab mới"));
        m_tabMoi->setShortcut(QKeySequence("Ctrl+T"));
    m_xoaTab = new QAction(QIcon("D:/Code/icon/Xoatab.png"), tr("Xóa tab hiện tại"));
        m_xoaTab->setShortcut(QKeySequence("Ctrl+R"));

    cacThaoTac << m_trangTruoc << m_trangSau << m_taiTrang << m_dungTai << m_trangChu;

    menuChucNang->addActions(cacThaoTac);
    menuChucNang->addAction(m_tabMoi);
    menuChucNang->addAction(m_xoaTab);

    QMenu *menuThongTin = menuBar()->addMenu(tr("?"));
    QAction *thongTin = new QAction(tr("Thông tin"));
        thongTin->setShortcut(QKeySequence("Ctrl+I"));

    menuThongTin->addAction(thongTin);

    connect(m_taiTrang, SIGNAL(triggered()), this, SLOT(thaoTacTaiTrang()));
    connect(m_dungTai, SIGNAL(triggered()), this, SLOT(thaoTacDungTai()));
    connect(m_trangChu, SIGNAL(triggered()), this, SLOT(thaoTacTrangChu()));
    connect(m_trangTruoc, SIGNAL(triggered()), this, SLOT(thaoTacTrangTruoc()));
    connect(m_trangSau, SIGNAL(triggered()), this, SLOT(thaoTacTrangSau()));
    connect(m_tabMoi, SIGNAL(triggered()), this, SLOT(thaoTacTabMoi()));
    connect(m_xoaTab, SIGNAL(triggered()), this, SLOT(thaoTacXoaTab()));
    connect(thongTin, SIGNAL(triggered()), this, SLOT(thongTin()));
}

void TrinhDuyet::khoiTaoToolBar(){
    m_thanhDiaChi = new QLineEdit();
    m_nutDi = new QPushButton(tr("Đi"));

    QToolBar *thanhCongCu = this->addToolBar("Thanh công cụ");
        thanhCongCu->addActions(cacThaoTac);
        thanhCongCu->addWidget(m_thanhDiaChi);
        thanhCongCu->addWidget(m_nutDi);

    connect(m_thanhDiaChi, SIGNAL(returnPressed()), this, SLOT(anEnterThanhDiaChi()));
    connect(m_nutDi, SIGNAL(clicked()), this, SLOT(anNutDi()));
}

void TrinhDuyet::khoiTaoStatusBar(){
    m_tienTrinhTaiTrang = new QProgressBar();
        m_tienTrinhTaiTrang->setRange(0, 100);
        m_tienTrinhTaiTrang->setVisible(false);
    statusBar()->addWidget(m_tienTrinhTaiTrang);
    statusBar()->setMaximumHeight(14);
}

QWebEngineView* TrinhDuyet::trangHienTai(){
   return m_cacTheTrang->currentWidget()->findChild<QWebEngineView *>();
}

QWidget* TrinhDuyet::taoTabMoi(){

    QWidget *trangThe = new QWidget();

    QWebEngineView *trangWeb = new QWebEngineView(trangThe);

    QVBoxLayout *lopSapXep = new QVBoxLayout();
        lopSapXep->setContentsMargins(0, 0, 0, 0);
        lopSapXep->addWidget(trangWeb);

    trangThe->setLayout(lopSapXep);

    trangWeb->load(QUrl("http://www.google.com"));

    connect(trangWeb, SIGNAL(loadStarted()), this, SLOT(batDauTienTrinh()));
    connect(trangWeb, SIGNAL(loadProgress(int)), this, SLOT(tienTrinh(int)));
    connect(trangWeb, SIGNAL(loadFinished(bool)), this, SLOT(taiXong()));
    connect(trangWeb, SIGNAL(titleChanged(QString)), this, SLOT(thayDoiTieuDe(QString)));
    connect(trangWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(thayDoiURL(QUrl)));

    return trangThe;
}

void TrinhDuyet::taiTrangWeb(QString url){
    trangHienTai()->load(QUrl(url));
}

void TrinhDuyet::thaoTacTaiTrang(){
    m_dungTai->setVisible(true);
    m_taiTrang->setVisible(false);
    trangHienTai()->reload();
}

void TrinhDuyet::thaoTacDungTai(){
    m_dungTai->setVisible(false);
    m_taiTrang->setVisible(true);
    trangHienTai()->stop();
}

void TrinhDuyet::thaoTacTrangTruoc(){
    trangHienTai()->back();
}

void TrinhDuyet::thaoTacTrangSau(){
    trangHienTai()->forward();
}

void TrinhDuyet::thaoTacTrangChu(){
    trangHienTai()->load(QUrl("https://www.google.com"));
}

void TrinhDuyet::thaoTacTabMoi(){
    int chiSoTrang = m_cacTheTrang->addTab(taoTabMoi(), tr("Tab mới"));
    m_cacTheTrang->setCurrentIndex(chiSoTrang);
}

void TrinhDuyet::thaoTacXoaTab(){
    if(m_cacTheTrang->count() == 1)
    {
        QMessageBox::warning(this, tr("Cảnh báo"), tr("Trình duyệt cần có ít nhất 1 tab!"));
        return;
    }
    else
    {
        m_cacTheTrang->removeTab(m_cacTheTrang->currentIndex());
    }
}

void TrinhDuyet::anNutDi(){
    QString url;
    if(m_thanhDiaChi->text() == trangHienTai()->url().toString()){
        return;
    }

    if(m_thanhDiaChi->text().isEmpty()){
        return;
    }

    if(m_thanhDiaChi->text().left(7) != "http://" && m_thanhDiaChi->text().left(8) != "https://"){
        url = "http://" + m_thanhDiaChi->text();
    }

    taiTrangWeb(url);
}

void TrinhDuyet::anEnterThanhDiaChi(){
    anNutDi();
}

void TrinhDuyet::thayDoiTab()
{
    thayDoiTieuDe(trangHienTai()->title());
}

void TrinhDuyet::batDauTienTrinh(){
    m_tienTrinhTaiTrang->setValue(0);
    m_tienTrinhTaiTrang->setVisible(true);
    m_taiTrang->setVisible(false);
    m_dungTai->setVisible(true);
}

void TrinhDuyet::tienTrinh(int tienTrinhDaTai){
    m_tienTrinhTaiTrang->setValue(tienTrinhDaTai);
}

void TrinhDuyet::taiXong(){
    m_tienTrinhTaiTrang->setVisible(false);
    statusBar()->showMessage(tr("Đã tải xong"), 2000);
    m_taiTrang->setVisible(true);
    m_dungTai->setVisible(false);

}

void TrinhDuyet::thayDoiTieuDe(QString tieuDe){
    if(tieuDe.size() > 40)
    {
        tieuDe = tieuDe.left(40) + "...";
    }

    int chiSoThe = m_cacTheTrang->currentIndex();
    m_cacTheTrang->setTabText(chiSoThe, tieuDe);
    setWindowTitle(tieuDe + " - Trình duyệt web");
}

void TrinhDuyet::thayDoiURL(QUrl url){
    m_thanhDiaChi->setText(url.toString());
}

void TrinhDuyet::thongTin(){
    QString thongTin;
    thongTin = tr("Trình duyệt web cơ bản tạo từ <b>Qt 5.12.11 MSVC 2017 64-bit</b>\n");
    thongTin += tr("<center>Ngày hoàn thiện: DD - MM - YYYY</center>");

    QMessageBox::information(this, tr("Thông tin"), thongTin);
}

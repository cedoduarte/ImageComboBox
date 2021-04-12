#include "ImageComboBox.h"
#include <QStylePainter>
#include <QFontMetricsF>
#include <QPaintEvent>
#include <QListWidget>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QMenu>

ImageComboBox::ImageComboBox(QWidget *parent)
    : QWidget(parent)
{
    m_listwidget = makeListWidget();
    m_menu = makeMenu();

    QStringList filenames {
        ":/Chrysanthemum.jpg",
        ":/Desert.jpg",
        ":/Hydrangeas.jpg",
        ":/Jellyfish.jpg",
        ":/Koala.jpg",
        ":/Lighthouse.jpg",
        ":/Tulips.jpg"
    };
    setImages(filenames);
}

ImageComboBox::ImageComboBox(const QStringList &filenames, QWidget *parent)
    : QWidget(parent)
{
    m_listwidget = makeListWidget();
    m_menu = makeMenu();
    setImages(filenames);
}

void ImageComboBox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);
    painter.drawComplexControl(QStyle::CC_ComboBox, makeComboBoxStyle());
    QFontMetrics fm = painter.fontMetrics();
    painter.drawText(5, 2 + fm.height(), m_currentFilename);
    QWidget::paintEvent(e);
}

void ImageComboBox::mousePressEvent(QMouseEvent *e)
{
    m_listwidget->setMinimumWidth(width());
    QPoint p = parentWidget()->mapToGlobal(pos());
    p.setY(p.y() + height());
    m_menu->popup(p);
    QWidget::mousePressEvent(e);
}

void ImageComboBox::onImageSelected(QListWidgetItem *item)
{
    setCurrentFilename(item->data(Qt::UserRole).toString());
    update();
    m_menu->hide();
}

void ImageComboBox::setImages(const QStringList &filenames)
{
    m_listwidget->clear();
    std::for_each(filenames.begin(), filenames.end(), [&](const QString &filename)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(filename));
        item->setText(QFileInfo(filename).fileName());
        item->setData(Qt::UserRole, filename);
        m_listwidget->addItem(item);
    });
}

QStringList ImageComboBox::images() const
{
    QStringList filenames;
    for (int x = 0; x < m_listwidget->count(); ++x)
    {
        filenames.append(m_listwidget->item(x)->data(Qt::UserRole).toString());
    }
    return filenames;
}

QMenu *ImageComboBox::makeMenu()
{
    QMenu *menu = new QMenu(this);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_listwidget);
    vbox->setMargin(0);
    vbox->setSpacing(0);
    menu->setLayout(vbox);
    return menu;
}

QListWidget *ImageComboBox::makeListWidget()
{
    QListWidget *listwidget = new QListWidget(this);
    listwidget->setMinimumSize(width(), 250);
    listwidget->setIconSize(QSize(50, 50));
    connect(listwidget, &QListWidget::itemClicked, this, &ImageComboBox::onImageSelected);
    return listwidget;
}

QStyleOptionComboBox ImageComboBox::makeComboBoxStyle()
{
    QStyleOptionComboBox option;
    option.initFrom(this);
    return option;
}

void ImageComboBox::setCurrentFilename(const QString &filename)
{
    if (m_currentFilename != filename)
    {
        if (images().contains(filename))
        {
            m_currentFilename = filename;
            emit currentFilenameChanged(m_currentFilename);
            emit currentImageChanged(QImage(m_currentFilename));
            emit currentPixmapChanched(QPixmap(m_currentFilename));
        }
    }
}

#ifndef IMAGECOMBOBOX_H
#define IMAGECOMBOBOX_H

#include <QWidget>
#include <QStyleOptionComboBox>

class QMenu;
class QListWidget;
class QListWidgetItem;

/** combobox de imágenes */
class ImageComboBox : public QWidget
{
    Q_OBJECT
public:
    /** constructor */
    ImageComboBox(QWidget *parent = nullptr);
    ImageComboBox(const QStringList &filenames, QWidget *parent = nullptr);

    /** asigna imagenes */
    void setImages(const QStringList &filenames);

    /** obtiene imágenes */
    QStringList images() const;

    /** asigna la imagen actual */
    void setCurrentFilename(const QString &filename);

    /** obtiene la imagen actual */
    QString currentFilename() const
    {
        return m_currentFilename;
    }

    /** obtiene la imagen actual */
    QImage currentImage() const
    {
        return QImage(m_currentFilename);
    }

    /** obtiene la imagen actual */
    QPixmap currentPixmap() const
    {
        return QPixmap(m_currentFilename);
    }
signals:
    /** archivo actual cambió */
    void currentFilenameChanged(const QString &filename);

    /** imagen actual cambió */
    void currentImageChanged(const QImage &image);

    /** pixmap actual cambió */
    void currentPixmapChanched(const QPixmap &pixmap);
protected:
    /** paint-event */
    void paintEvent(QPaintEvent *e) override;

    /** mouse-event */
    void mousePressEvent(QMouseEvent *e) override;
private slots:
    /** imagen seleccionada */
    void onImageSelected(QListWidgetItem *item);
private:
    /** crea menú */
    QMenu *makeMenu();

    /** crea lista de imágenes */
    QListWidget *makeListWidget();

    /** crea el estilo del combobox */
    QStyleOptionComboBox makeComboBoxStyle();

    QMenu *m_menu; //!< menú
    QListWidget *m_listwidget; //!< listwidget
    QString m_currentFilename; //!< imagen actual
};

#endif // IMAGECOMBOBOX_H

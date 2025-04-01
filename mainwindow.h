#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "layermodel.h"
#include <QMainWindow>
#include "sizedialog.h"
#include "sprite.h"
#include "spriteeditor.h"
#include <QColorDialog>
#include <tool.h>
#include "layerview.h"
#include <sprite.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(SizeDialog *setSizeWindow, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void initEditor(int canvasDim);
    void cloneLayer();
    void removeLayer(int layerIndex);
    void openColor();
    void setColor();
    void cloneFrame();
    void removeFrame();
    void setAnimationPreview(QPixmap image);
    void saveSprite();
    //void loadSprite();

signals:
    void requestMirror(int layerIndex);

private:
    Ui::MainWindow *ui;
    QColorDialog* colorWindow;
    Tool* editTools;

    SpriteEditor *editor;  // Pointer to the sprite editor
    Sprite *sprite;
    LayerModel *layerModel;
    LayerView *layerView;

    // Get the tool tips and the icons for each of the buttons.
    void setUpIcons();
    void setUpConnections(const int canvasDim);
    void closeEvent(QCloseEvent *event) override;
    void mirror();
    int lastFrameIndex;
    int activeFrameIndex = 0;
    int lastLayerIndex;
    QSize animationPreviewDimensions;
};

#endif // MAINWINDOW_H

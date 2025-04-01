#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "sizedialog.h"
#include "layermodel.h"
#include "layerview.h"
#include "sprite.h"
#include "spriteeditor.h"
#include "tool.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Mainwindow that is displayed to the user
 *
 * This class provides functionalities for sprite and layer management, color selection,
 * animation preview, and interaction with various tools within the pixel editor.
 *
 * @authors Landon Huking, Dean Smith, Alex Lancaster, Canon Curtis, & Elijah Tolton
 * @date March 31, 2025
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow Object
     * @param setSizeWindow - A pointer to the size configuration dialog
     * @param parent - The parent widget (default is nullptr)
     */
    explicit MainWindow(SizeDialog *setSizeWindow, QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object and frees resources
     */
    ~MainWindow();

public slots:
    /**
     * @brief Initializes the sprite editor with a specified canvas dimension.
     * @param canvasDim - The size of the canvas in pixels.
     */
    void initEditor(int canvasDim);

    /**
     * @brief Clones the currently selected layer in the view and add it to the layerView layout
     */
    void cloneLayer();

    /**
     * @brief Removes a layer from the view
     * @param layerIndex - The index of the layer to be removed
     */
    void removeLayer(int layerIndex);

    /**
     * @brief Opens the color picker dialog
     */
    void openColor();

    /**
     * @brief Sets the currently selected color
     */
    void setColor();

    /**
     * @brief Clones the currently selected frame and add it to the frameView layout
     */
    void cloneFrame();

    /**
     * @brief Removes the last frame in the frame preview
     */
    void removeFrame();

    /**
     * @brief Updates the animation preview with a given image
     * @param image - The QPixmap representing the frame to be previewed.
     */
    void setAnimationPreview(QPixmap image);
    
    void updateCurrentFrame(int index);

    void saveSprite();
    
    void loadSprite();

signals:
    /**
     * @brief Emits a signal to request mirroring of a specific layer
     * @param layerIndex - The index of the layer to be mirrored.
     */
    void requestMirror(int layerIndex);

private:
    /**
     * @brief The user interface instance
     */
    Ui::MainWindow *ui;

    /**
     * @brief The color picker dialog instance
     */
    QColorDialog *colorWindow;

    /**
     * @brief The editing tool instance used for drawing and erasing
     */
    Tool *editTools;

    /**
     * @brief The sprite editor instance for handling drawing
     */
    SpriteEditor *editor;

    /**
     * @brief The sprite instance being edited
     */
    Sprite *sprite;

    /**
     * @brief The model managing layers within the editor
     */
    LayerModel *layerModel;

    /**
     * @brief The layer view instance displaying available layers
     */
    LayerView *layerView;
    FrameView *activeFrame;

    std::vector<FrameView*> frameWidgets;

    /**
     * @brief Sets up the icons for UI buttons
     */
    void setUpIcons();

    /**
     * @brief Establishes connections between UI components and their respective slots
     * @param canvasDim - The size of the canvas in pixels.
     */
    void setUpConnections(const int canvasDim);

    /**
     * @brief Handles the close event to ensure proper cleanup
     * @param event - The close event instance
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief Performs a mirroring operation on the active layer
     */
    void mirror();

    /**
     * @brief The index of the last frame in the frameView layout
     */
    int lastFrameIndex;

    /**
     * @brief The index of the currently active frame
     */
    int activeFrameIndex = 0;

    /**
     * @brief The index of the last layer in the layerView layout
     */
    int lastLayerIndex;

    /**
     * @brief The dimensions of the animation preview
     */
    QSize animationPreviewDimensions;
};

#endif // MAINWINDOW_H

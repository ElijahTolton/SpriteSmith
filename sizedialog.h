#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>

namespace Ui { class SizeDialog; }

/**
 * @brief The initial size dialog window which sets the canvas size in pixels
 *
 * @author Alex Lancaster
 * @date March 29, 2025
 */
class SizeDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for SizeDialog object
     * @param parent - QWidget parent of SizeDialog
     */
    explicit SizeDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructor for SizeDialog
     */
    ~SizeDialog();

public slots:

    /**
     * @brief Called when the apply button is hit when setting canvas dimensions
     */
    void emitSetSize();

signals:
    /**
     * @brief Emits the size of the canvas
     * @param canvasSize - The width and height of the canvas in pixels
     */
    void setSize(int canvasSize);

private:
    /**
     * @brief User interface instance
     */
    Ui::SizeDialog *ui;

    /**
     * @brief Logic behind user closing the dialog
     * @param What the user selected
     */
    void closeEvent(QCloseEvent *event) override;

};

#endif // SIZEDIALOG_H

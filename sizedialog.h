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
     * @brief SizeDialog
     * @param parent
     */
    explicit SizeDialog(QWidget *parent = nullptr);

    /**
     *
     */
    ~SizeDialog();

public slots:

    /**
     * @brief emitSetSize
     */
    void emitSetSize();

signals:
    /**
     * @brief setSize
     * @param canvasSize
     */
    void setSize(int canvasSize);

private:
    /**
     * @brief ui
     */
    Ui::SizeDialog *ui;

    /**
     * @brief closeEvent
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

};

#endif // SIZEDIALOG_H

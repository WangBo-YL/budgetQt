#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include "BudgetClass.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void navigateToPage(int pageNum);
    void loadItemsToTable(const std::string& budgetName);

private slots:

    void on_budgetMenuButton_clicked();

    void on_returnFromBudgetMenuButton_clicked();

    void on_newBudgetButton_clicked();

    void on_budgetListButton_clicked();

    void on_cancelCreateBudgetButton_clicked();

    void on_createNewBudgetButton_clicked();

    void on_finishAddItemButton_clicked();

    void on_addItemToBudgetButton_clicked();

    void on_returnFromBudgetListButton_clicked();

    void on_addItemButton_clicked();

private:
    Ui::MainWindow *ui;
    Budget budget;
    std::string budgetName;
    std::vector<Budget::item> items;
    std::vector<Budget> budgets;
    std::vector<Budget::category> categorys;

};
#endif // MAINWINDOW_H

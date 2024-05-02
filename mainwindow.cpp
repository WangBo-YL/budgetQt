#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
  {
    ui->setupUi(this);
    // sqlite3* db;
    // int rc;
    // rc = sqlite3_open_v2("budget.db", &db, SQLITE_OPEN_READWRITE, NULL);
    // if(rc != SQLITE_OK)
    // {
    //     qDebug() << "Error opening database : " << sqlite3_errmsg(db);
    //     sqlite3_close(db);
    //     return;
    // }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::navigateToPage(int pageNum)
{
    ui->stackedWidget->setCurrentIndex(pageNum);
}

void MainWindow::loadItemsToTable(const std::string& name)
{
    std::vector<Budget::item> items = budget.getItemList(name);
    ui->itemTableWidget->setRowCount(0);

    for(const auto& item: items)
    {
        int row = ui->itemTableWidget->rowCount();
        ui->itemTableWidget->insertRow(row);

        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(item.name));
        QTableWidgetItem* capItem = new QTableWidgetItem(QString::number(item.cap));
        QTableWidgetItem* totalItem = new QTableWidgetItem(QString::number(item.total));

        ui->itemTableWidget->setItem(row, 0, nameItem);
        ui->itemTableWidget->setItem(row, 1, capItem);
        ui->itemTableWidget->setItem(row, 2, totalItem);

    }
}


void MainWindow::on_budgetMenuButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_returnFromBudgetMenuButton_clicked()
{
    navigateToPage(0);
}


void MainWindow::on_newBudgetButton_clicked()
{
    navigateToPage(2);
}


void MainWindow::on_budgetListButton_clicked()
{
    navigateToPage(4);
}


void MainWindow::on_cancelCreateBudgetButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_createNewBudgetButton_clicked()
{
    budgetName = ui->newBudgetNameInput->text().toStdString();
    if(ui->newBudgetNameInput->text().isEmpty())
    {
        QMessageBox::warning(this,"Input Error","Budget name cannot be empty.");
    }else
    {
        navigateToPage(3);
    }
}



void MainWindow::on_finishAddItemButton_clicked()
{
    budgetName = "";
    items.clear();
    ui->itemNameInput->clear();
    ui->itemLimitInput->clear();
    ui->categoryInput->clear();
    ui->newBudgetNameInput->clear();
    navigateToPage(1);
}


void MainWindow::on_addItemToBudgetButton_clicked()
{


}


void MainWindow::on_returnFromBudgetListButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_addItemButton_clicked()
{
    std::string itemName = ui->itemNameInput->text().toStdString();
    double itemCap = ui->itemLimitInput->text().toDouble();
    std::string category = ui->categoryInput->text().toStdString();
    double budgetTotal = 0;
    budgetTotal += itemCap;
    Budget::category newCategory;
    newCategory.name = category;
    Budget::item newItem;
    newItem.name = itemName;
    newItem.cap = itemCap;
    newItem.total = budgetTotal;
    try {
        items.push_back(newItem);
        budget.addBudget(budgetName,budgetTotal,items);
        QMessageBox::information(this,"Success", "Item added to budget.");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }

    ui->itemNameInput->clear();
    ui->itemLimitInput->clear();
    ui->categoryInput->clear();
    loadItemsToTable(budget.getBudgetName());
}


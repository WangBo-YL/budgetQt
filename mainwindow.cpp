#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    navigateToPage(0);
    updateBudgetCombobox();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::navigateToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::updateBudgetCombobox()
{
    ui->budgetComboBox->clear();
    std::vector<std::string> budgetsName;
    Budget budget= Budget();
    budgetsName = budget.getBudgetList();
    if(budgetsName.empty())
    {
        qDebug() << "Empty list" ;
    }
    for(int i = 0; i < budgetsName.size(); ++i)
    {
        QString nameToStr = QString::fromStdString(budgetsName[i]);
        ui->budgetComboBox->addItem(nameToStr);
    }
}

void MainWindow::updateBudgetListWidget()
{
    QListWidget* budgetList = ui->budgetListWidget;
    budgetList->clear();
    std::vector<std::string> budgetsName;
    Budget budget= Budget();
    budgetsName = budget.getBudgetList();
    if(budgetsName.empty())
    {
        qDebug() << "Empty list" ;
    }else{
        for(int i = 0; i < budgetsName.size(); ++i)
        {
            QString nameToStr = QString::fromStdString(budgetsName[i]);
            QListWidgetItem* newItem = new QListWidgetItem(nameToStr);
            ui->budgetListWidget->addItem(newItem);
        }
    }
}


void MainWindow::updateItemListWidget()
{
    std::string budgetName = budgetListItem->text().toStdString();
    qDebug() << "The budget name is : " << budgetName;
    QListWidget* itemList = ui->itemListWidget;
    itemList->clear();
    Budget budget= Budget();
    std::vector<Budget::item> items;
    items = budget.getItemList(budgetName);
    if(items.empty())
    {
        qDebug() << "Empty list" ;
    }else{
        for(int i = 0; i < items.size(); ++i)
        {
            QString nameToStr = QString::fromStdString("Name: ");
            nameToStr += QString::fromStdString(items[i].name);
            nameToStr += QString::fromStdString(" |Limit: ");
            nameToStr += QString::fromStdString(std::to_string(items[i].cap));
            nameToStr += QString::fromStdString(" |Total: ");
            nameToStr += QString::fromStdString(std::to_string(items[i].total));

            qDebug() << "The item is " << nameToStr;
            QListWidgetItem* newItem = new QListWidgetItem(nameToStr);
            ui->itemListWidget->addItem(newItem);
        }
    }

}

void MainWindow::on_budgetMenuButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_expenseMenuButton_clicked()
{
    navigateToPage(6);
}


void MainWindow::on_savingsMenuButton_clicked()
{
    navigateToPage(10);
}


void MainWindow::on_transactionHistoryButton_clicked()
{
    navigateToPage(9);

}


void MainWindow::on_reportMenuButton_clicked()
{
    navigateToPage(8);

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
    updateBudgetListWidget();
    navigateToPage(4);

}


void MainWindow::on_newItemButton_clicked()
{
    navigateToPage(3);

}


void MainWindow::on_cancelCreateBudgetButton_clicked()
{
    navigateToPage(1);

}


void MainWindow::on_saveBudgetButton_clicked()
{

    std::string budgetName = ui->newBudgetNameInput->text().toStdString();
    if(budgetName.empty())
    {
        qDebug() << "the budget name is empty.";
        QMessageBox::warning(this,"Error","You have to input the budget name.");
        return;
    }
    std::string itemName = ui->newItemNameInput_2->text().toStdString();
    if(itemName.empty())
    {
        qDebug() << "the item name is empty.";
        QMessageBox::warning(this,"Error","You have to input the item name.");
        return;
    }
    double itemLimit = ui->newItemLimitInput_2->text().toDouble();
    double itemTotal = ui->newItemTotalInput_2->text().toDouble();
    if(itemLimit<0 || itemTotal <0)
    {
        qDebug() << "The input can't be less than 0.";
        QMessageBox::warning(this,"Error", "You have to input a positive value.");
        return;
    }
    Budget::item item;
    item.name = itemName;
    item.cap = itemLimit;
    item.total = itemTotal;
    std::vector<Budget::item> items;
    items.push_back(item);
    Budget budget = Budget();
    budget.addBudget(budgetName,0,items);

    updateBudgetCombobox();
    // updateBudgetListWidget();
    ui->newBudgetNameInput->clear();
    ui->newItemNameInput_2->clear();
    ui->newItemLimitInput_2->clear();
    ui->newItemTotalInput_2->clear();
    navigateToPage(1);

}



void MainWindow::on_returnFromBudgetListButton_clicked()
{
    navigateToPage(1);

}


void MainWindow::on_budgetDetaiButton_clicked()
{
    updateItemListWidget();
    navigateToPage(5);
}


void MainWindow::on_deleteBudgetButton_clicked()
{
    std::string budgetName = budgetListItem->text().toStdString();
    qDebug() << "The budget name is : " << budgetName;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Delete Budget", "Delete Budget?",QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        Budget budget = Budget();
        budget.deleteBudget(budgetName);
        delete budgetListItem;
        budgetListItem = nullptr;
        qDebug() << "Budget deleted successfully.";
    }
}


// void MainWindow::on_newItemCapSlider_sliderMoved(int position)
// {

// }


void MainWindow::on_cancelAddItemButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_addItemButton_clicked()
{

    std::string budgetName = ui->budgetComboBox->currentText().toStdString();
    std::string itemName = ui->newItemNameInput->text().toStdString();
    if(itemName.empty())
    {
        qDebug() << "the item name is empty.";
        QMessageBox::warning(this,"Error","You have to input the item name.");
        return;
    }
    double itemLimit = ui->newItemLimitInput->text().toDouble();
    double itemTotal = ui->newItemTotalInput->text().toDouble();
    if(itemLimit<0 || itemTotal <0)
    {
        qDebug() << "The input can't be less than 0.";
        QMessageBox::warning(this,"Error", "You have to input a positive value.");
        return;
    }
    Budget::item item;
    item.name = itemName;
    item.cap = itemLimit;
    item.total = itemTotal;
    Budget budget = Budget();
    budget.addItem(budgetName,item);

    ui->newItemNameInput->clear();
    ui->newItemLimitInput->clear();
    ui->newItemTotalInput->clear();
    navigateToPage(1);

}


void MainWindow::on_cancelExpenseButton_clicked()
{
    navigateToPage(6);
}


void MainWindow::on_confirmExpenseButton_clicked()
{
    navigateToPage(6);

}


void MainWindow::on_returnFromExpenseMenuButton_clicked()
{
    navigateToPage(0);
}


void MainWindow::on_addExpenditureButton_clicked()
{
    navigateToPage(7);

}


void MainWindow::on_returnFromItemListButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_deleteItemButton_clicked()
{

    std::string itemName = itemListItems->text().toStdString();
    qDebug() << "The item name is : " << itemName;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Delete Item", "Delete Item?",QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        std::vector<Budget::item> items;
        Budget budget = Budget();
        items = budget.getItemList(budgetListItem->text().toStdString());
        qDebug() << "the budget name I passed in is: " <<budgetListItem->text().toStdString();
        budget.deleteItem(items[itemIndex].name);
        delete itemListItems;
        itemListItems = nullptr;
        qDebug() << "Budget deleted successfully.";
    }

}


void MainWindow::on_cancelAddIncomeButton_clicked()
{
    navigateToPage(1);
}


void MainWindow::on_finishAddIncomeButton_clicked()
{
    navigateToPage(10);

}


void MainWindow::on_cancelSavingPlanButton_clicked()
{
    navigateToPage(10);
}


void MainWindow::on_finishAddSavingPlanButton_clicked()
{
    navigateToPage(10);

}


void MainWindow::on_returnFromReportPageButton_clicked()
{
    navigateToPage(0);
}


void MainWindow::on_returnFromSavingsListButton_clicked()
{
    navigateToPage(10);
}


void MainWindow::on_editSavingListButton_clicked()
{
    navigateToPage(11);

}


void MainWindow::on_deleteSavingsListButton_clicked()
{

}


void MainWindow::on_returnFromSavingButton_clicked()
{
    navigateToPage(0);
}


void MainWindow::on_newSavingPlanButton_clicked()
{
    navigateToPage(11);

}


void MainWindow::on_savingsListButton_clicked()
{
    navigateToPage(12);
}


void MainWindow::on_addIncomeButton_clicked()
{
    navigateToPage(13);
}


void MainWindow::on_returnFromTransPage_clicked()
{
    navigateToPage(0);
}




void MainWindow::on_budgetListWidget_itemClicked(QListWidgetItem *item)
{
    bool hasSelection = ui->budgetListWidget->selectedItems().isEmpty();
    if(!hasSelection)
    {
        ui->budgetDetaiButton->show();
        ui->deleteBudgetButton->show();
        budgetListItem = item;
        QString budgetName = item->text();
        qDebug() << "Budget selected is: " << budgetName;
    }else{
        ui->budgetDetaiButton->hide();
        ui->deleteBudgetButton->hide();
    }
}


void MainWindow::on_itemListWidget_itemClicked(QListWidgetItem *item)
{
    bool hasSelection = ui->itemListWidget->selectedItems().isEmpty();
    if(!hasSelection)
    {
        ui->deleteItemButton->show();
        itemListItems = item;
        itemIndex = ui->itemListWidget->row(item);
        qDebug() << "Selected item index: " <<itemIndex;
    }else{
        ui->budgetDetaiButton->hide();
        ui->deleteBudgetButton->hide();
    }
}


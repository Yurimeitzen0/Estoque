#include "global_functions.h"

Global_functions::Global_functions()
{

}

void Global_functions::Clean_TableView(QTableWidget * tableView)
{
    while (tableView->rowCount() > 0)
    {
        tableView->removeRow(0);
    }
}

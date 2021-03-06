#include "central_left_widget.h"
#include <QDebug>

namespace meow {
namespace ui {
namespace main_window {

CentralLeftWidget::CentralLeftWidget(models::db::EntitiesTreeModel * dbEntitiesTreeModel,
        QWidget * parent)
    :QWidget(parent),
     _dbEntitiesTreeModel(dbEntitiesTreeModel)
{
    createMainLayout();
}

void CentralLeftWidget::createMainLayout()
{
    _mainLayout = new QVBoxLayout();
    _mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(_mainLayout);

    _dbTree = new QTreeView();
    _dbTree->setHeaderHidden(true);
    _dbTree->setModel(_dbEntitiesTreeModel);
    _mainLayout->addWidget(_dbTree);

    connect(_dbTree->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &CentralLeftWidget::selectedDbEntityChanged
    );
}

void CentralLeftWidget::selectedDbEntityChanged(
    const QItemSelection &selected,
    const QItemSelection &deselected)
{

    Q_UNUSED(deselected);

    QModelIndex index;
    QModelIndexList items = selected.indexes();

    if (!items.isEmpty()) {
        index = items.at(0);

        try {
            _dbEntitiesTreeModel->selectEntityAt(index);
        } catch(meow::db::Exception & ex) {
            qDebug() << "Tree error: " << ex.message();
            // TODO: show error
            // revert selection
        }

    } else {
        qDebug() << "Tree: selection is empty";
    }
}

} // namespace meow
} // namespace ui
} // namespace main_window

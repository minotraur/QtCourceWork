#include "MyModel.h"

#include <QColor>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

PersonsModel::PersonsModel( QObject* parent ) : QAbstractTableModel( parent ) {
}

int PersonsModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_persons.count();
}

int PersonsModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return LAST;
}

QVariant PersonsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || m_persons.count() <= index.row() || ( role != Qt::DisplayRole && role != Qt::EditRole )) {
        return QVariant();
    }
        return m_persons[ index.row() ][ Column( index.column() ) ];
}

bool PersonsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if( !index.isValid() || role != Qt::EditRole || m_persons.count() <= index.row() ) {
            return false;
        }

    m_persons[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}
Qt::ItemFlags PersonsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    flags |= Qt::ItemIsEditable;
//    if( index.isValid() ) {
//        if( index.column() == SELECTION ) {
//            flags |= Qt::ItemIsEditable;
//        }
//    }
    return flags;
}

void PersonsModel::appendPerson(const QString& id, const QString& name, const QString& city)
{
    PersonData person;
    person[ ID ] = id;
    person[ NAME ] = name;
    person[ CITY ] = city;
    int row = m_persons.count();
    beginInsertRows( QModelIndex(), row, row );
    m_persons.append( person );
    endInsertRows();
}

void PersonsModel::changeData(const QString& id, const QString& name, const QString& city)
{
    return;
}

void PersonsModel::saveData()
{
    QList<QString> data;
    Persons::iterator it = m_persons.begin();
    while(it != m_persons.end())
    {
        data.append(it->value(ID).toString()+",");
        data.append(it->value(NAME).toString()+",");
        data.append(it->value(CITY).toString());
        ++it;
    }
    QString filename = QFileDialog::getSaveFileName(0, "Save Dialog", "/Users/vlad/Desktop","*.csv");
    QFile file(filename);
    if(file.open(QFile::WriteOnly)){
        QTextStream out(&file);
        qDebug()<<"Открыл";
        for(int i=0;i<data.size();i++)
        {
            out<<data[i].toUtf8();
            qDebug() <<"Попробовал записать";
            if((i+1)%3==0)
                out<<'\n';
        }
        file.close();
    }
    else
        qDebug()<<"Ошибка записи";
}


void PersonsModel::dowloadData()
{
    QList<QString *> data;
    QString filename = QFileDialog::getOpenFileName(0, "Open Dialog", "/Users/vlad/Desktop", "*.csv");
    QFile file(filename);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
            qDebug() << "File not exists";
    }
    else {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                for (QString item : line.split(","))
                {
                    data.append(new QString((item.replace("\"",""))));
                }
            }
            file.close();
        }

    if(!data.empty())
    {
        for(int i=0;!data.empty();i++)
        {
            PersonData person;
            person[ ID ]=*data.first();
            data.pop_front();
            person[ NAME ] = *data.first();
            data.pop_front();
            person[ CITY ] =*data.first();
            data.pop_front();
            person[ SELECTION ] = false;
            int row = m_persons.count();



            beginInsertRows( QModelIndex(), row, row );

            m_persons.append( person );

            endInsertRows();
        }
    }
}

void PersonsModel::removeSelected(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_persons.removeAt(row);
    endRemoveRows();
}

QVariant PersonsModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return section;
    }
    switch( section ) {
    case ID:
        return tr( "ID" );
    case NAME:
        return tr( "Фамилия" );
    case CITY:
        return tr("Город");
    }
    return QVariant();
}

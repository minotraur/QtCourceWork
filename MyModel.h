#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class PersonsModel : public QAbstractTableModel {
    Q_OBJECT
public:
    PersonsModel( QObject* parent = 0 );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void appendPerson( const QString& id, const QString& name, const QString& city);
    void changeData( const QString& id, const QString& name, const QString& city);
    void dowloadData();
    void saveData();

public slots:
    void removeSelected(int row);

private:

    enum Column {
        ID,
        NAME,
        CITY,
        SELECTION,
        LAST = 3
    };

    typedef QHash< Column, QVariant > PersonData;
    typedef QList< PersonData > Persons;
    Persons m_persons;

};

#endif // MYMODEL_H


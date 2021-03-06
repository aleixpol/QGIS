/***************************************************************************
    qgslayoutmanager.h
    ------------------
    Date                 : January 2017
    Copyright            : (C) 2017 Nyall Dawson
    Email                : nyall dot dawson at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSLAYOUTMANAGER_H
#define QGSLAYOUTMANAGER_H

#include "qgis_core.h"
#include "qgis.h"
#include "qgsmasterlayoutinterface.h"
#include <QObject>

class QgsProject;
class QgsPrintLayout;

/**
 * \ingroup core
 * \class QgsLayoutManager
 *
 * \brief Manages storage of a set of layouts.
 *
 * QgsLayoutManager handles the storage, serializing and deserializing
 * of print layouts and reports. Usually this class is not constructed directly, but
 * rather accessed through a QgsProject via QgsProject::layoutManager().
 *
 * QgsLayoutManager retains ownership of all the layouts contained
 * in the manager.
 * \since QGIS 3.0
 */

class CORE_EXPORT QgsLayoutManager : public QObject
{
    Q_OBJECT

  public:

    /**
     * Constructor for QgsLayoutManager. The project will become the parent object for this
     * manager.
     */
    explicit QgsLayoutManager( QgsProject *project SIP_TRANSFERTHIS = nullptr );

    ~QgsLayoutManager() override;

    /**
     * Adds a \a layout to the manager. Ownership of the layout is transferred to the manager.
     * Returns true if the addition was successful, or false if the layout could not be added (eg
     * as a result of a duplicate layout name).
     * \see removeLayout()
     * \see layoutAdded()
     */
    bool addLayout( QgsMasterLayoutInterface *layout SIP_TRANSFER );

    /**
     * Removes a \a layout from the manager. The layout is deleted.
     * Returns true if the removal was successful, or false if the removal failed (eg as a result
     * of removing a layout which is not contained in the manager).
     * \see addLayout()
     * \see layoutRemoved()
     * \see layoutAboutToBeRemoved()
     * \see clear()
     */
    bool removeLayout( QgsMasterLayoutInterface *layout );

    /**
     * Removes and deletes all layouts from the manager.
     * \see removeLayout()
     */
    void clear();

    /**
     * Returns a list of all layouts contained in the manager.
     */
    QList< QgsMasterLayoutInterface * > layouts() const;

    /**
     * Returns a list of all print layouts contained in the manager.
     */
    QList< QgsPrintLayout * > printLayouts() const;

    /**
     * Returns the layout with a matching name, or nullptr if no matching layouts
     * were found.
     */
    QgsMasterLayoutInterface *layoutByName( const QString &name ) const;

    /**
     * Reads the manager's state from a DOM element, restoring all layouts
     * present in the XML document.
     * \see writeXml()
     */
    bool readXml( const QDomElement &element, const QDomDocument &doc );

    /**
     * Returns a DOM element representing the state of the manager.
     * \see readXml()
     */
    QDomElement writeXml( QDomDocument &doc ) const;

    /**
     * Duplicates an existing \a layout from the manager. The new
     * layout will automatically be stored in the manager.
     * Returns new the layout if duplication was successful.
     */
    QgsMasterLayoutInterface *duplicateLayout( const QgsMasterLayoutInterface *layout, const QString &newName );

    /**
     * Generates a unique title for a new layout of the specified \a type, which does not
     * clash with any already contained by the manager.
     */
    QString generateUniqueTitle( QgsMasterLayoutInterface::Type type = QgsMasterLayoutInterface::PrintLayout ) const;

  signals:

    //! Emitted when a layout is about to be added to the manager
    void layoutAboutToBeAdded( const QString &name );

    //! Emitted when a layout has been added to the manager
    void layoutAdded( const QString &name );

    //! Emitted when a layout was removed from the manager
    void layoutRemoved( const QString &name );

    //! Emitted when a layout is about to be removed from the manager
    void layoutAboutToBeRemoved( const QString &name );

    //! Emitted when a layout is renamed
    void layoutRenamed( QgsMasterLayoutInterface *layout, const QString &newName );

  private:

    QgsProject *mProject = nullptr;

    QList< QgsMasterLayoutInterface * > mLayouts;

};

#endif // QGSLAYOUTMANAGER_H

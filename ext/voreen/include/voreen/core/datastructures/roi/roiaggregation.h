/***********************************************************************************
 *                                                                                 *
 * Voreen - The Volume Rendering Engine                                            *
 *                                                                                 *
 * Copyright (C) 2005-2013 University of Muenster, Germany.                        *
 * Visualization and Computer Graphics Group <http://viscg.uni-muenster.de>        *
 * For a list of authors please refer to the file "CREDITS.txt".                   *
 *                                                                                 *
 * This file is part of the Voreen software package. Voreen is free software:      *
 * you can redistribute it and/or modify it under the terms of the GNU General     *
 * Public License version 2 as published by the Free Software Foundation.          *
 *                                                                                 *
 * Voreen is distributed in the hope that it will be useful, but WITHOUT ANY       *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR   *
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.      *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License in the file   *
 * "LICENSE.txt" along with this file. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                                 *
 * For non-commercial academic use see the license exception specified in the file *
 * "LICENSE-academic.txt". To get information about commercial licensing please    *
 * contact the authors.                                                            *
 *                                                                                 *
 ***********************************************************************************/

#ifndef VRN_ROIAGGREGATION_H
#define VRN_ROIAGGREGATION_H

#include "voreen/core/datastructures/roi/roibase.h"

namespace voreen {

class VRN_CORE_API ROIAggregation : public ROIBase {
protected:
    ROIAggregation() : ROIBase() {}
public:
    ROIAggregation(Grid grid);
    ~ROIAggregation();

    virtual std::vector<ROIBase*> getChildren();
    virtual std::vector<const ROIBase*> getChildren() const;

    virtual void addChild(ROIBase* c);
    virtual void removeChild(ROIBase* c);
    virtual void deregisterChild(ROIBase* c);

    virtual void serialize(XmlSerializer& s) const;
    virtual void deserialize(XmlDeserializer& s);

protected:
    std::vector<ROIBase*> children_;
    static const std::string loggerCat_;
};

} //namespace

#endif

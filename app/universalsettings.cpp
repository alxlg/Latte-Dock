/*
*  Copyright 2017  Smith AR <audoban@openmailbox.org>
*                  Michail Vourlakos <mvourlakos@gmail.com>
*
*  This file is part of Latte-Dock
*
*  Latte-Dock is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License as
*  published by the Free Software Foundation; either version 2 of
*  the License, or (at your option) any later version.
*
*  Latte-Dock is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "universalsettings.h"

namespace Latte {

UniversalSettings::UniversalSettings(KSharedConfig::Ptr config, QObject *parent)
    : QObject(parent),
      m_universalGroup(KConfigGroup(config, QStringLiteral("UniversalSettings")))
{
    connect(this, &UniversalSettings::versionChanged, this, &UniversalSettings::saveConfig);
}

UniversalSettings::~UniversalSettings()
{
    saveConfig();
    m_universalGroup.sync();
}

void UniversalSettings::load()
{
    loadConfig();
}

int UniversalSettings::version() const
{
    return m_version;
}

void UniversalSettings::setVersion(int ver)
{
    if (m_version == ver) {
        return;
    }

    m_version = ver;

    emit versionChanged();
}

void UniversalSettings::loadConfig()
{
    m_version = m_universalGroup.readEntry("version", 1);
}

void UniversalSettings::saveConfig()
{
    m_universalGroup.writeEntry("version", m_version);
}


}

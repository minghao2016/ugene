/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2020 UniPro <ugene@unipro.ru>
 * http://ugene.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "ConservationPlotSupport.h"

#include <U2Core/AppContext.h>
#include <U2Core/Settings.h>

#include "R/RSupport.h"
#include "python/PythonSupport.h"
#include "utils/ExternalToolUtils.h"

namespace U2 {

const QString ConservationPlotSupport::ET_CONSERVATION_PLOT = "conservation_plot";
const QString ConservationPlotSupport::ET_CONSERVATION_PLOT_ID = "USUPP_CONSERVATION_PLOT";
const QString ConservationPlotSupport::CONSERVATION_DIR_NAME = "phastCons";
const QString ConservationPlotSupport::CONSERVATION_DATA_NAME = "conservation_data";

ConservationPlotSupport::ConservationPlotSupport()
    : ExternalTool(ConservationPlotSupport::ET_CONSERVATION_PLOT_ID, "cistrome", ConservationPlotSupport::ET_CONSERVATION_PLOT) {
    initialize();
}

void ConservationPlotSupport::initialize() {
    if (AppContext::getMainWindow() != nullptr) {
        icon = QIcon(":external_tool_support/images/cmdline.png");
        grayIcon = QIcon(":external_tool_support/images/cmdline_gray.png");
        warnIcon = QIcon(":external_tool_support/images/cmdline_warn.png");
    }

    toolKitName = "Cistrome";
    description = ConservationPlotSupport::tr("<i>ConservationPlot</i> - Draw conservation plot for many bed files.");

    executableFileName = "conservation_plot.py";

    toolRunnerProgram = PythonSupport::ET_PYTHON_ID;
    dependencies << PythonSupport::ET_PYTHON_ID
                 << RSupport::ET_R_ID;

    validMessage = "conservation_plot.py ";
    validationArguments << "--version";

    versionRegExp = QRegExp(executableFileName + " (\\d+\\.\\d+)");

    ExternalToolUtils::addDefaultCistromeDirToSettings();
    ExternalToolUtils::addCistromeDataPath(CONSERVATION_DATA_NAME, CONSERVATION_DIR_NAME, true);

    muted = true;
}

}    // namespace U2

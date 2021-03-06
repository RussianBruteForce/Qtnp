﻿/*
 *This file is part of Qtnp.
 *
 * Qtnp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qtnp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qtnp.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fparser.h"

using namespace mu;

ExpParser::ExpParser()
{
	Parser p;
}

void ExpParser::setE(QString str)
{
	p.SetExpr(str.toStdString());
}

double ExpParser::getR(value_type x)
{
	try {
		p.DefineVar("x",&x);
		return p.Eval();
	} catch (Parser::exception_type &e) {
		emit badExp(QString::fromStdString(e.GetMsg()));
		return 666; // FOR THE SATAN
	}
}

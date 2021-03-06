/* qTorrent - An open-source, cross-platform BitTorrent client
 * Copyright (C) 2017 Petko Georgiev
 *
 * panel.cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "panel.h"
#include <QToolButton>

#define ICON_SIZE QSize(80, 60)
#define DEFAULT_COLOR "#414141"
#define CHECKED_COLOR "#262626"
#define HOVERED_COLOR "#505050"
#define HOVERED_CHECKED_COLOR "#303030"
#define PRESSED_COLOR "#323232"

Panel::Panel(QWidget *parent)
	: QToolBar("Torrents Filter Panel", parent)
	, m_allIcon(QIcon(":/button-all.png"))
	, m_completedIcon(QIcon(":/button-completed.png"))
	, m_downloadingIcon(QIcon(":/button-downloading.png"))
	, m_uploadingIcon(QIcon(":/button-uploading.png"))
	, m_settingsIcon(QIcon(":/button-settings.png"))

	, m_allIconActive(QIcon(":/button-all-active.png"))
	, m_completedIconActive(QIcon(":/button-completed-active.png"))
	, m_downloadingIconActive(QIcon(":/button-downloading-active.png"))
	, m_uploadingIconActive(QIcon(":/button-uploading-active.png"))
	, m_settingsIconActive(QIcon(":/button-settings-active.png"))

	, m_all(new QToolButton)
	, m_completed(new QToolButton)
	, m_downloading(new QToolButton)
	, m_uploading(new QToolButton)
	, m_settings(new QToolButton)
{
	m_toolButtons.append(m_all);
	m_toolButtons.append(m_completed);
	m_toolButtons.append(m_downloading);
	m_toolButtons.append(m_uploading);
	m_toolButtons.append(m_settings);

	resetButtons();

	for (auto button : m_toolButtons) {
		button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
		button->setCheckable(true);
		button->setAutoExclusive(true);
		addWidget(button);
	}

	setIconSize(ICON_SIZE);
	setStyleSheet("QToolBar { background: " DEFAULT_COLOR "; border: none; spacing: 0px; } "
				  "QToolButton { background-color: " DEFAULT_COLOR "; border: none } "
				  "QToolButton:checked { background-color: " CHECKED_COLOR " } "
				  "QToolButton:hover { background-color: " HOVERED_COLOR " } "
				  "QToolButton:hover:checked { background-color: " HOVERED_CHECKED_COLOR " } "
				  "QToolButton:pressed { background-color: " PRESSED_COLOR " }");

	setFloatable(false);

	connect(m_all, SIGNAL(clicked()), this, SLOT(openAll()));
	connect(m_completed, SIGNAL(clicked()), this, SLOT(openCompleted()));
	connect(m_downloading, SIGNAL(clicked()), this, SLOT(openDownloading()));
	connect(m_uploading, SIGNAL(clicked()), this, SLOT(openUploading()));
	connect(m_settings, SIGNAL(clicked()), this, SLOT(openSettings()));
}

Panel::~Panel()
{
	for (auto button : m_toolButtons) {
		delete button;
	}
}


Panel::Section Panel::getCurrentSection()
{
	if (m_all->isChecked()) {
		return Section::All;
	} else if (m_completed->isChecked()) {
		return Section::Completed;
	} else if (m_downloading->isChecked()) {
		return Section::Downloading;
	} else if (m_uploading->isChecked()) {
		return Section::Uploading;
	} else if (m_settings->isChecked()) {
		return Section::Settings;
	}
	Q_ASSERT(false);
	return Section::All;
}

void Panel::resetButtons()
{
	m_all->setIcon(m_allIcon);
	m_completed->setIcon(m_completedIcon);
	m_downloading->setIcon(m_downloadingIcon);
	m_uploading->setIcon(m_uploadingIcon);
	m_settings->setIcon(m_settingsIcon);
}

void Panel::openAll()
{
	resetButtons();
	m_all->setIcon(m_allIconActive);
	m_all->setChecked(true);
	emit showAll();
	emit hideSettings();
}

void Panel::openCompleted()
{
	resetButtons();
	m_completed->setIcon(m_completedIconActive);
	m_completed->setChecked(true);
	emit showCompleted();
	emit hideSettings();
}

void Panel::openDownloading()
{
	resetButtons();
	m_downloading->setIcon(m_downloadingIconActive);
	m_downloading->setChecked(true);
	emit showDownloading();
	emit hideSettings();
}

void Panel::openUploading()
{
	resetButtons();
	m_uploading->setIcon(m_uploadingIconActive);
	m_uploading->setChecked(true);
	emit showUploading();
	emit hideSettings();
}

void Panel::openSettings()
{
	resetButtons();
	m_settings->setIcon(m_settingsIconActive);
	m_settings->setChecked(true);
	emit showSettings();
}

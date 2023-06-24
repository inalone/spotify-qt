#pragma once

#include "lib/spotify/track.hpp"

#include <QListWidgetItem>

class Tooltip
{
public:
	static void set(QListWidgetItem *item, const lib::spt::track &track);
	static void set(QListWidgetItem *item, const lib::spt::track &track, const QPixmap &albumImage);

private:
	static constexpr int iconSize = 16;
	static constexpr int albumSize = 64;

	Tooltip() = default;

	static auto tooltip(const lib::spt::track &track, const QPixmap &albumImage) -> QString;

	static auto icon(const QString &name, int size = iconSize) -> QString;
	static auto icon(const QPixmap &pixmap) -> QString;
};

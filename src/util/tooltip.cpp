#include "util/tooltip.hpp"
#include "util/icon.hpp"

#include <QBuffer>

void Tooltip::set(QListWidgetItem *item, const lib::spt::track &track)
{
	item->setToolTip(tooltip(track, {}));
}

void Tooltip::set(QListWidgetItem *item, const lib::spt::track &track, const QPixmap &albumImage)
{
	item->setToolTip(tooltip(track, albumImage));
}

auto Tooltip::tooltip(const lib::spt::track &track, const QPixmap &albumImage) -> QString
{
	const QString table(
		"<table>"
		"	<tr>"
		// Album art
		"		<td rowspan=\"3\">"
		"			<img src=\"%1\"/>"
		"		</td>"
		// Track icon
		"		<td>"
		"			<img src=\"%2\"/>"
		"		</td>"
		// Track name
		"		<td>%3</td>"
		"	</tr>"
		"	<tr>"
		// Artist icon
		"		<td>"
		"			<img src=\"%4\"/>"
		"		</td>"
		// Artist name
		"		<td>%5</td>"
		"	</tr>"
		"	<tr>"
		// Album icon
		"		<td>"
		"			<img src=\"%6\"/>"
		"		</td>"
		// Album name
		"		<td>%7</td>"
		"	</tr>"
		"</table>"
	);

	const auto artists = lib::spt::entity::combine_names(track.artists);

	const auto albumIcon = albumImage.isNull()
		? icon(QStringLiteral("media-optical-audio"), albumSize)
		: icon(albumImage);

	return table.arg(albumIcon,
		icon(QStringLiteral("view-media-track")),
		QString::fromStdString(track.name),
		icon(QStringLiteral("view-media-artist")),
		QString::fromStdString(artists),
		icon(QStringLiteral("view-media-album-cover")),
		QString::fromStdString(track.album.name));
}

auto Tooltip::icon(const QString &name, int size) -> QString
{
	const auto iconData = Icon::get(name);
	const auto pixmap = iconData.pixmap(size, size);
	return icon(pixmap);
}

auto Tooltip::icon(const QPixmap &pixmap) -> QString
{
	QByteArray data;
	QBuffer buffer(&data);
	pixmap.save(&buffer, "PNG");
	return QString("data:image/png;base64,%1").arg(data.toBase64());
}

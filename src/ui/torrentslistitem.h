#ifndef TORRENTSLISTITEM_H
#define TORRENTSLISTITEM_H

#include <QTreeWidgetItem>
#include <QVariant>
#include <QMap>

class QTorrent;
class Torrent;

class TorrentsListItem : public QObject, public QTreeWidgetItem {
	Q_OBJECT

public:
	enum Section {
		Name=0, Size, Peers, Progress, Downloaded, Uploaded
	};

	TorrentsListItem(QTorrent* qTorrent, QTreeWidget* view, Torrent* torrent);

	void setSortData(int column, QVariant data);
	bool operator<(const QTreeWidgetItem& other) const;
	void refresh();
	// true if this torrent belongs to the currently opened section
	bool belongsToSection();

	Torrent* torrent() const;

	void setName(const QString& value);
	void setSize(qint64 value);
	void setPeers(int value);
	void setProgress(float value);
	void setDownloaded(qint64 value);
	void setUploaded(qint64 value);

public slots:
	void onPauseAction();
	void onStartAction();

private:
	QTorrent* m_qTorrent;
	Torrent* m_torrent;
	QMap<int, QVariant> m_sortData;
	static QString toPrettySize(qint64 bytes);
};

#endif // TORRENTSLISTITEM_H

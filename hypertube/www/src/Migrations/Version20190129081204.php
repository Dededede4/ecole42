<?php declare(strict_types=1);

namespace DoctrineMigrations;

use Doctrine\DBAL\Schema\Schema;
use Doctrine\Migrations\AbstractMigration;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
final class Version20190129081204 extends AbstractMigration
{
    public function up(Schema $schema) : void
    {
        // this up() migration is auto-generated, please modify it to your needs
        $this->abortIf($this->connection->getDatabasePlatform()->getName() !== 'sqlite', 'Migration can only be executed safely on \'sqlite\'.');

        $this->addSql('CREATE TABLE subtitle (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, video_id VARCHAR(255) NOT NULL, text CLOB NOT NULL, created_at DATETIME NOT NULL)');
        $this->addSql('CREATE INDEX IDX_518597B129C1004E ON subtitle (video_id)');
        $this->addSql('CREATE TEMPORARY TABLE __temp__video AS SELECT btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, source, bytes, downloadable, process_started FROM video');
        $this->addSql('DROP TABLE video');
        $this->addSql('CREATE TABLE video (btih VARCHAR(255) NOT NULL COLLATE BINARY, title VARCHAR(255) NOT NULL COLLATE BINARY, torrent_url VARCHAR(255) NOT NULL COLLATE BINARY, nb_download INTEGER DEFAULT NULL, nb_seeder INTEGER DEFAULT NULL, nb_leecher INTEGER DEFAULT NULL, production_date DATETIME DEFAULT NULL, picture_url VARCHAR(255) DEFAULT NULL COLLATE BINARY, notation INTEGER DEFAULT NULL, download_started_at DATETIME DEFAULT NULL, download_finish_at DATETIME DEFAULT NULL, download_bytes_done INTEGER DEFAULT NULL, nb_see INTEGER DEFAULT NULL, genre INTEGER DEFAULT NULL, description CLOB DEFAULT NULL COLLATE BINARY, casting CLOB DEFAULT NULL COLLATE BINARY, duration INTEGER DEFAULT NULL, last_see_at DATETIME DEFAULT NULL, source INTEGER NOT NULL, bytes INTEGER DEFAULT NULL, downloadable BOOLEAN NOT NULL, process_started BOOLEAN NOT NULL, PRIMARY KEY(btih))');
        $this->addSql('INSERT INTO video (btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, source, bytes, downloadable, process_started) SELECT btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, source, bytes, downloadable, process_started FROM __temp__video');
        $this->addSql('DROP TABLE __temp__video');
        $this->addSql('DROP INDEX IDX_9474526C29C1004E');
        $this->addSql('DROP INDEX IDX_9474526CA76ED395');
        $this->addSql('CREATE TEMPORARY TABLE __temp__comment AS SELECT id, user_id, video_id, text, created_at FROM comment');
        $this->addSql('DROP TABLE comment');
        $this->addSql('CREATE TABLE comment (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER NOT NULL, video_id VARCHAR(255) NOT NULL COLLATE BINARY, text CLOB NOT NULL COLLATE BINARY, created_at DATETIME NOT NULL, CONSTRAINT FK_9474526CA76ED395 FOREIGN KEY (user_id) REFERENCES user (id) NOT DEFERRABLE INITIALLY IMMEDIATE, CONSTRAINT FK_9474526C29C1004E FOREIGN KEY (video_id) REFERENCES video (btih) NOT DEFERRABLE INITIALLY IMMEDIATE)');
        $this->addSql('INSERT INTO comment (id, user_id, video_id, text, created_at) SELECT id, user_id, video_id, text, created_at FROM __temp__comment');
        $this->addSql('DROP TABLE __temp__comment');
        $this->addSql('CREATE INDEX IDX_9474526C29C1004E ON comment (video_id)');
        $this->addSql('CREATE INDEX IDX_9474526CA76ED395 ON comment (user_id)');
    }

    public function down(Schema $schema) : void
    {
        // this down() migration is auto-generated, please modify it to your needs
        $this->abortIf($this->connection->getDatabasePlatform()->getName() !== 'sqlite', 'Migration can only be executed safely on \'sqlite\'.');

        $this->addSql('DROP TABLE subtitle');
        $this->addSql('DROP INDEX IDX_9474526CA76ED395');
        $this->addSql('DROP INDEX IDX_9474526C29C1004E');
        $this->addSql('CREATE TEMPORARY TABLE __temp__comment AS SELECT id, user_id, video_id, text, created_at FROM comment');
        $this->addSql('DROP TABLE comment');
        $this->addSql('CREATE TABLE comment (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER NOT NULL, video_id VARCHAR(255) NOT NULL, text CLOB NOT NULL, created_at DATETIME NOT NULL)');
        $this->addSql('INSERT INTO comment (id, user_id, video_id, text, created_at) SELECT id, user_id, video_id, text, created_at FROM __temp__comment');
        $this->addSql('DROP TABLE __temp__comment');
        $this->addSql('CREATE INDEX IDX_9474526CA76ED395 ON comment (user_id)');
        $this->addSql('CREATE INDEX IDX_9474526C29C1004E ON comment (video_id)');
        $this->addSql('ALTER TABLE video ADD COLUMN subtitle VARCHAR(255) DEFAULT NULL COLLATE BINARY');
    }
}

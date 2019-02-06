<?php declare(strict_types=1);

namespace DoctrineMigrations;

use Doctrine\DBAL\Schema\Schema;
use Doctrine\Migrations\AbstractMigration;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
final class Version20190121181214 extends AbstractMigration
{
    public function up(Schema $schema) : void
    {
        // this up() migration is auto-generated, please modify it to your needs
        $this->abortIf($this->connection->getDatabasePlatform()->getName() !== 'sqlite', 'Migration can only be executed safely on \'sqlite\'.');

        $this->addSql('DROP INDEX UNIQ_8D93D649C05FB297');
        $this->addSql('DROP INDEX UNIQ_8D93D649A0D96FBF');
        $this->addSql('DROP INDEX UNIQ_8D93D64992FC23A8');
        $this->addSql('CREATE TEMPORARY TABLE __temp__user AS SELECT id, username, username_canonical, email, email_canonical, enabled, salt, password, last_login, confirmation_token, password_requested_at, roles, facebook_id, intra42_id, firstname, lastname FROM user');
        $this->addSql('DROP TABLE user');
        $this->addSql('CREATE TABLE user (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username VARCHAR(180) NOT NULL COLLATE BINARY, username_canonical VARCHAR(180) NOT NULL COLLATE BINARY, email VARCHAR(180) NOT NULL COLLATE BINARY, email_canonical VARCHAR(180) NOT NULL COLLATE BINARY, enabled BOOLEAN NOT NULL, salt VARCHAR(255) DEFAULT NULL COLLATE BINARY, password VARCHAR(255) NOT NULL COLLATE BINARY, last_login DATETIME DEFAULT NULL, confirmation_token VARCHAR(180) DEFAULT NULL COLLATE BINARY, password_requested_at DATETIME DEFAULT NULL, roles CLOB NOT NULL COLLATE BINARY --(DC2Type:array)
        , facebook_id INTEGER DEFAULT NULL, intra42_id INTEGER DEFAULT NULL, firstname VARCHAR(255) NOT NULL, lastname VARCHAR(255) NOT NULL, profile_picture_path VARCHAR(255) DEFAULT NULL)');
        $this->addSql('INSERT INTO user (id, username, username_canonical, email, email_canonical, enabled, salt, password, last_login, confirmation_token, password_requested_at, roles, facebook_id, intra42_id, firstname, lastname) SELECT id, username, username_canonical, email, email_canonical, enabled, salt, password, last_login, confirmation_token, password_requested_at, roles, facebook_id, intra42_id, firstname, lastname FROM __temp__user');
        $this->addSql('DROP TABLE __temp__user');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_8D93D649C05FB297 ON user (confirmation_token)');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_8D93D649A0D96FBF ON user (email_canonical)');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_8D93D64992FC23A8 ON user (username_canonical)');
        $this->addSql('CREATE TEMPORARY TABLE __temp__video AS SELECT btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, subtitle, source FROM video');
        $this->addSql('DROP TABLE video');
        $this->addSql('CREATE TABLE video (btih VARCHAR(255) NOT NULL COLLATE BINARY, title VARCHAR(255) NOT NULL COLLATE BINARY, torrent_url VARCHAR(255) NOT NULL COLLATE BINARY, nb_download INTEGER DEFAULT NULL, nb_seeder INTEGER DEFAULT NULL, nb_leecher INTEGER DEFAULT NULL, production_date DATETIME DEFAULT NULL, picture_url VARCHAR(255) DEFAULT NULL COLLATE BINARY, notation INTEGER DEFAULT NULL, download_started_at DATETIME DEFAULT NULL, download_finish_at DATETIME DEFAULT NULL, download_bytes_done INTEGER DEFAULT NULL, nb_see INTEGER DEFAULT NULL, genre INTEGER DEFAULT NULL, description CLOB DEFAULT NULL COLLATE BINARY, casting CLOB DEFAULT NULL COLLATE BINARY, duration INTEGER DEFAULT NULL, last_see_at DATETIME DEFAULT NULL, subtitle VARCHAR(255) DEFAULT NULL COLLATE BINARY, source INTEGER NOT NULL, PRIMARY KEY(btih))');
        $this->addSql('INSERT INTO video (btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, subtitle, source) SELECT btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, subtitle, source FROM __temp__video');
        $this->addSql('DROP TABLE __temp__video');
    }

    public function down(Schema $schema) : void
    {
        // this down() migration is auto-generated, please modify it to your needs
        $this->abortIf($this->connection->getDatabasePlatform()->getName() !== 'sqlite', 'Migration can only be executed safely on \'sqlite\'.');

        $this->addSql('DROP INDEX UNIQ_8D93D64992FC23A8');
        $this->addSql('DROP INDEX UNIQ_8D93D649A0D96FBF');
        $this->addSql('DROP INDEX UNIQ_8D93D649C05FB297');
        $this->addSql('CREATE TEMPORARY TABLE __temp__user AS SELECT id, username, username_canonical, email, email_canonical, enabled, salt, password, last_login, confirmation_token, password_requested_at, roles, firstname, lastname, facebook_id, intra42_id FROM user');
        $this->addSql('DROP TABLE user');
        $this->addSql('CREATE TABLE user (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username VARCHAR(180) NOT NULL, username_canonical VARCHAR(180) NOT NULL, email VARCHAR(180) NOT NULL, email_canonical VARCHAR(180) NOT NULL, enabled BOOLEAN NOT NULL, salt VARCHAR(255) DEFAULT NULL, password VARCHAR(255) NOT NULL, last_login DATETIME DEFAULT NULL, confirmation_token VARCHAR(180) DEFAULT NULL, password_requested_at DATETIME DEFAULT NULL, roles CLOB NOT NULL --(DC2Type:array)
        , facebook_id INTEGER DEFAULT NULL, intra42_id INTEGER DEFAULT NULL, firstname VARCHAR(255) DEFAULT NULL COLLATE BINARY, lastname VARCHAR(255) DEFAULT NULL COLLATE BINARY)');
        $this->addSql('INSERT INTO user (id, username, username_canonical, email, email_canonical, enabled, salt, password, last_login, confirmation_token, password_requested_at, roles, firstname, lastname, facebook_id, intra42_id) SELECT id, username, username_canonical, email, email_canonical, enabled, salt, password, last_login, confirmation_token, password_requested_at, roles, firstname, lastname, facebook_id, intra42_id FROM __temp__user');
        $this->addSql('DROP TABLE __temp__user');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_8D93D64992FC23A8 ON user (username_canonical)');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_8D93D649A0D96FBF ON user (email_canonical)');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_8D93D649C05FB297 ON user (confirmation_token)');
        $this->addSql('CREATE TEMPORARY TABLE __temp__video AS SELECT btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, subtitle, source FROM video');
        $this->addSql('DROP TABLE video');
        $this->addSql('CREATE TABLE video (btih VARCHAR(255) NOT NULL, title VARCHAR(255) NOT NULL, torrent_url VARCHAR(255) NOT NULL, nb_download INTEGER DEFAULT NULL, nb_seeder INTEGER DEFAULT NULL, nb_leecher INTEGER DEFAULT NULL, production_date DATETIME DEFAULT NULL, picture_url VARCHAR(255) DEFAULT NULL, notation INTEGER DEFAULT NULL, download_started_at DATETIME DEFAULT NULL, download_finish_at DATETIME DEFAULT NULL, download_bytes_done INTEGER DEFAULT NULL, nb_see INTEGER DEFAULT NULL, genre INTEGER DEFAULT NULL, description CLOB DEFAULT NULL, casting CLOB DEFAULT NULL, duration INTEGER DEFAULT NULL, last_see_at DATETIME DEFAULT NULL, subtitle VARCHAR(255) DEFAULT NULL, source INTEGER DEFAULT NULL, PRIMARY KEY(btih))');
        $this->addSql('INSERT INTO video (btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, subtitle, source) SELECT btih, title, torrent_url, nb_download, nb_seeder, nb_leecher, production_date, picture_url, notation, download_started_at, download_finish_at, download_bytes_done, nb_see, genre, description, casting, duration, last_see_at, subtitle, source FROM __temp__video');
        $this->addSql('DROP TABLE __temp__video');
    }
}

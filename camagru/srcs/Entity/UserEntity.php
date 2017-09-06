<?php

namespace Entity;

/**
 * @table user
 */
class UserEntity
{
    /**
     * @name id
     * @type INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY
     */
    private $id;

    /**
     * @name username
     * @type VARCHAR(255) NOT NULL
     */
    private $username;

    /**
     * @name mail
     * @type VARCHAR(255) NOT NULL
     */
    private $mail;

    /**
     * @name password
     * @type VARCHAR(255) NOT NULL
     */
    private $password;

    /**
     * @name salt
     * @type VARCHAR(255) NOT NULL
     */
    private $salt;
}
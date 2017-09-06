<?php

namespace Entity;

class UserEntity
{
    /**
     * @name id
     * @type idf
     */
    private $id;

    /**
     * @name username
     * @type varchar
     */
    private $username;

    /**
     * @name mail
     * @type varchar
     */
    private $mail;

    /**
     * @name password
     * @type varchar
     */
    private $password;

    /**
     * @name salt
     * @type varchar
     */
    private $salt;
}
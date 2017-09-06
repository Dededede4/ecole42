<?php

namespace Framework\ORM;


use Framework\Parser\ConfigParserInterface;


class EntityManager
{
    private $parser;

    public function __construct(ConfigParserInterface $parser)
    {
        $this->parser = $parser;
    }

    public function schemaUpdateEntity($path)
    {
        $this->parser->setPath($path);
        $config = $this->parser->getConfig();
    }

    public function schemaUpdate()
    {
        return;
        var_dump($this->parser->setPath(ROOTDIR.'/srcs/Entity', 'Entity', 'Entity\\'));
        die;

        /*
         * $q = new Query();
            $q->selectIn('user')
                ->addAndWhere('user = \'dededede4\'')
                ->addOrWhere('admin = 1');

            echo new MysqlBuilder($q)."\n";
            $q->updateIn('user');
            echo new MysqlBuilder($q)."\n";
            $q->deleteIn('user');
            echo new MysqlBuilder($q)."\n";

            $q = new Query();
            $q->create('user')
                ->addCol('PersonID int')
                ->addCol('LastName varchar(255)');
            echo new MysqlBuilder($q)."\n";
         */
    }

}
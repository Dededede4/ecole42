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

    public function schemaCreate()
    {
        $results = $this->parser->setPath(ROOTDIR.'/srcs/Entity', 'Entity', 'Entity\\');

        foreach ($results as $result)
        {
            $q = new Query();
            $q->create($result['fileconfig']['table'][0]);
            foreach ($result['results'] as $col)
            {
                $q->addCol($col['name'][0].' '.implode(' ', $col['type']));
            }
            echo new MysqlBuilder($q)."\n";
        }
        die;
    }

}
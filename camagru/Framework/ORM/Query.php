<?php

namespace Framework\ORM;

class Query implements QueryInterface
{
    private $action;

    private $table;

    private $filters = array();

    private $orders = array();

    private $havings = array();

    private $groups = array();

    private $sets = array();

    private $cols = array();

    public function selectIn($table)
    {
        $this->action = QueryInterface::SELECT;
        $this->table = $table;

        return $this;
    }

    public function updateIn($table)
    {
        $this->action = QueryInterface::UPDATE;
        $this->table = $table;

        return $this;
    }

    public function deleteIn($table)
    {
        $this->action = QueryInterface::DELETE;
        $this->table = $table;

        return $this;
    }

    public function create($table)
    {
        $this->action = QueryInterface::CREATE;
        $this->table = $table;

        return $this;
    }

    public function addAndWhere($eq)
    {
        $this->filters[] = array(
            'action' => QueryInterface::SQL_AND,
            'eq' => $eq,
        );

        return $this;
    }

    public function addOrWhere($eq)
    {
        $this->filters[] = array(
            'action' => QueryInterface::SQL_OR,
            'eq' => $eq,
        );

        return $this;
    }

    public function addAndHavings($eq)
    {
        $this->havings[] = array(
            'action' => QueryInterface::SQL_AND,
            'eq' => $eq,
        );

        return $this;
    }

    public function addOrHavings($eq)
    {
        $this->havings[] = array(
            'action' => QueryInterface::SQL_OR,
            'eq' => $eq,
        );

        return $this;
    }

    public function addOrder($eq)
    {
        $this->orders[] = $eq;

        return $this;
    }

    public function addGroup($eq)
    {
        $this->groups[] = $eq;

        return $this;
    }

    public function addSet($eq)
    {
        $this->sets[] = $eq;

        return $this;
    }

    public function addCol($eq)
    {
        $this->cols[] = $eq;

        return $this;
    }

    public function getTable()
    {
        return $this->table;
    }

    public function getFilters()
    {
        return $this->filters;
    }

    public function getOrders()
    {
        return $this->orders;
    }

    public function getHavings()
    {
        return $this->havings;
    }

    public function getAction()
    {
        return $this->action;
    }

    public function getGroups()
    {
        return $this->groups;
    }

    public function getSets()
    {
        return $this->sets;
    }

    public function getCols()
    {
        return $this->cols;
    }
}

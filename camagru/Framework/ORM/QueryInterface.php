<?php

namespace Framework\ORM;

interface QueryInterface
{
    const SELECT = 'SELECT';
    const UPDATE = 'UPDATE';
    const DELETE = 'DELETE';
    const CREATE = 'CREATE';
    const SQL_AND = 'AND';
    const SQL_OR = 'OR';

    public function selectIn($table);

    public function updateIn($table);

    public function deleteIn($table);

    public function create($table);

    public function addAndWhere($eq);

    public function addOrWhere($eq);

    public function addAndHavings($eq);

    public function addOrHavings($eq);

    public function addOrder($eq);

    public function addGroup($eq);

    public function addSet($eq);

    public function addCol($eq);

    public function getTable();

    public function getFilters();

    public function getOrders();

    public function getHavings();

    public function getAction();

    public function getGroups();

    public function getSets();

    public function getCols();
}
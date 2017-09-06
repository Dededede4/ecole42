<?php

namespace Framework\ORM;

class MysqlBuilder
{
    private $qb;

    public function __construct(QueryInterface $qb)
    {
        $this->qb = $qb;
    }

    private function getPartFromArray(array $array)
    {
        $query = '';
        foreach ($array as $key => $filter) {
            if ($key > 0) {
                $query .= ' '.$filter['action'].' '.$filter['eq'];
            } else {
                $query .= ' '.$filter['eq'];
            }
        }

        return $query;
    }

    public function __toString()
    {
        $qb = $this->qb;
        $query = '';
        if (QueryInterface::SELECT === $qb->getAction()) {
            $query = 'SELECT * FROM '.$qb->getTable();

            if ($qb->getFilters()) {
                $query .= ' WHERE'.$this->getPartFromArray($qb->getFilters());
            }
            if ($qb->getGroups()) {
                $query .= ' GROUP BY '.implode(', ', $qb->getGroups());
            }
            if ($qb->getHavings()) {
                $query .= ' HAVING'.$this->getPartFromArray($qb->getHavings());
            }
            if ($qb->getOrders()) {
                $query .= ' ORDER BY '.implode(', ', $qb->getOrders());
            }
        }
        if (QueryInterface::UPDATE === $qb->getAction()) {
            $query = 'UPDATE '.$qb->getTable();

            if ($qb->getSets()) {
                $query = 'SET '.implode(', ', $qb->getSets());
            }

            if ($qb->getFilters()) {
                $query .= ' WHERE'.$this->getPartFromArray($qb->getFilters());
            }
        }
        if (QueryInterface::DELETE === $qb->getAction()) {
            $query = 'DELETE FROM '.$qb->getTable();
            if ($qb->getFilters()) {
                $query .= ' WHERE'.$this->getPartFromArray($qb->getFilters());
            }
        }
        if (QueryInterface::CREATE === $qb->getAction()) {
            $query = 'CREATE TABLE '.$qb->getTable().' ( '.implode(', ', $qb->getCols()).' )';
        }

        return $query;

    }
}

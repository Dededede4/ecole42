<?php

namespace App\Entity;

class Search
{
    private $seederMin;

    private $seederMax;

    private $search;

    private $productionYearMin;

    private $productionYearMax;

    private $notationMin;

    private $notationMax;

    private $genre;

    private $orderBy;

    private $sortBy;



    public function getSeederMin()
    {
        return $this->seederMin;
    }

    public function setSeederMin($seederMin): self
    {
        $this->seederMin = $seederMin;

        return $this;
    }

    public function getSeederMax()
    {
        return $this->seederMax;
    }

    public function setSeederMax($seederMax): self
    {
        $this->seederMax = $seederMax;

        return $this;
    }

    public function getSearch(): ?string
    {
        return $this->search;
    }

    public function setSearch(?string $search): self
    {
        $this->search = $search;

        return $this;
    }

    public function getProductionYearMin()
    {
        return $this->productionYearMin;
    }

    public function setProductionYearMin($productionYearMin): self
    {
        $this->productionYearMin = $productionYearMin;

        return $this;
    }

    public function getProductionYearMax()
    {
        return $this->productionYearMax;
    }

    public function setProductionYearMax($productionYearMax): self
    {
        $this->productionYearMax = $productionYearMax;

        return $this;
    }

    public function getNotationMin()
    {
        return $this->notationMin;
    }

    public function setNotationMin($notationMin): self
    {
        $this->notationMin = $notationMin;

        return $this;
    }

    public function getNotationMax()
    {
        return $this->notationMax;
    }

    public function setNotationMax($notationMax): self
    {
        $this->notationMax = $notationMax;

        return $this;
    }

    public function getGenre()
    {
        return $this->genre;
    }

    public function setGenre($genre): self
    {
        $this->genre = $genre;

        return $this;
    }

    public function getOrderBy()
    {
        return $this->orderBy;
    }

    public function setOrderBy($orderBy): self
    {
        $this->orderBy = $orderBy;

        return $this;
    }

    public function getSortBy()
    {
        return $this->sortBy;
    }

    public function setSortBy($sortBy): self
    {
        $this->sortBy = $sortBy;

        return $this;
    }
}

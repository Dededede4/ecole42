<?php

class Subject implements SplSubject
{
    private $observers = array();

    public function attach(SplObserver $observer)
    {
        $this->observers[] = $observer;
    }

    public function detach(SplObserver $observer)
    {
        $newObservers = array();
        foreach ($this->observers as $observerRegistered)
        {
            if ($observerRegistered !== $observer)
            {
                $newObservers[] = $observerRegistered;
            }
        }
        $this->observers = $newObservers;
    }

    public function notify()
    {
        foreach ($this->observers as $observerRegistered)
        {
            $observerRegistered->update($this);
        }
    }
}
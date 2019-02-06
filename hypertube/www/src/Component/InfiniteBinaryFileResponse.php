<?php

namespace App\Component;

use Symfony\Component\HttpFoundation\BinaryFileResponse;

class InfiniteBinaryFileResponse extends BinaryFileResponse
{
    public function sendContent()
    {
        if (!$this->isSuccessful()) {
            return parent::sendContent();
        }

        if (0 === $this->maxlen) {
            return $this;
        }

        $out = fopen('php://output', 'wb');
        $file = fopen($this->file->getPathname(), 'rb');

        while(1)
        {
            stream_copy_to_stream($file, $out, $this->maxlen, $this->offset);
            sleep(1);
        }

        fclose($out);
        fclose($file);


        if ($this->deleteFileAfterSend) {
            unlink($this->file->getPathname());
        }

        return $this;
    }
}
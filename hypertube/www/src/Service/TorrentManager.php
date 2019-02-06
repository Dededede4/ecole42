<?php

namespace App\Service;

use App\Entity\Video;
use Symfony\Component\DependencyInjection\ParameterBag\ParameterBagInterface;

use PhpAmqpLib\Connection\AMQPStreamConnection;
use PhpAmqpLib\Message\AMQPMessage;


class TorrentManager
{
	private $parameters;

	public function __construct(ParameterBagInterface $parameters)
	{
		$this->parameters = $parameters;
	}
	public function download($video)
	{
		// Download torrent file
		$webPath = $this->parameters->get('kernel.project_dir') . '/public/'; 
        $torrentPath = $webPath.'/download/torrent/'.$video->getBtih().'.torrent';
		$torrentFile = file_get_contents($video->getTorrentUrl());
		file_put_contents($torrentPath, $torrentFile);

		// Send the message
		$rabbitConnection = new AMQPStreamConnection('localhost', 5672, 'guest', 'guest');
		$ch = $rabbitConnection->channel();

		$ch->queue_declare(
		  'torrent-to-download', //nom de notre file d'attente
		  false,            //passif
		  true,             //durable
		  false,            //exclusif
		  false             //auto-suppression
		);

		$amqpMessage = new AMQPMessage($video->getBtih());

  		$ch->basic_publish($amqpMessage, '', 'torrent-to-download');

  		$ch->close();
		$rabbitConnection->close();
	}
}
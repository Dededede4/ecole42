<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use App\Entity\Video;
use App\Entity\Subtitle;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\HttpFoundation\Request;

use Psr\Log\LoggerInterface;


class UpdateController extends AbstractController
{
    /**
     * @Route("/video/{video}/add/subtitle", name="addsubtitle")
     */
    public function downloadAction(Video $video, Request $request)
    {
    	if ($request->getClientIp() !== '127.0.0.1')
    		return new Response();
    	$val = json_decode($request->getContent(), true);
    	$entityManager = $this->getDoctrine()->getManager();
    	foreach ($val['names'] as $name) {
    		$subtitle = new Subtitle();
    		$subtitle->setVideo($video)
    				->setText($name)
    				->setCreatedAt(new \DateTime())
    				;
    		$entityManager->persist($subtitle);
    	}

        $entityManager->flush();
    	return new Response();
    }

      /**
     * @Route("/video/{video}/add/size", name="addstrem")
     */
    public function addSizeAction(Video $video, Request $request, LoggerInterface $logger)
    {
    	if ($request->getClientIp() !== '127.0.0.1')
    		return new Response();
    	$val = json_decode($request->getContent(), true);

    	$video->setDownloadBytesDone($val['length'], true);

    	if ($video->getDuration() && $video->getDownloadStartedAt())
    	{
	    	$secondDownload = (new \DateTime())->getTimestamp() - $video->getDownloadStartedAt()->getTimestamp();
	    	$estimatedDownloadDuration = $secondDownload * $video->getBytes() / $video->getDownloadBytesDone();
	    	if ($estimatedDownloadDuration - $secondDownload < $video->getDuration())
	    	{
	    		$video->setDownloadable(true);
	    	}
	    }
	    else
	    {
	    	$percentDone = 100 * $video->getDownloadBytesDone() / $video->getBytes();
	    	if ($percentDone > 20)
	    	{
	    		$video->setDownloadable(true);
	    	}
	    }



    	$entityManager = $this->getDoctrine()->getManager();
        $entityManager->persist($video);
        $entityManager->flush();
    	return new Response();
    }

    /**
     * @Route("/video/{video}/set/size", name="setsize")
     */
    public function setSizeAction(Video $video, Request $request, LoggerInterface $logger)
    {
    	if ($request->getClientIp() !== '127.0.0.1')
    		return new Response();
    	$video->setDownloadStartedAt(new \DateTime());
    	$val = json_decode($request->getContent(), true);

    	$video->setBytes($val['length']);

    	$entityManager = $this->getDoctrine()->getManager();
        $entityManager->persist($video);
        $entityManager->flush();
    	return new Response();
    }
}
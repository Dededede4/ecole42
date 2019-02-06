<?php

namespace App\Service;

use Symfony\Component\DomCrawler\Crawler;

use App\Entity\Video;

class SearchTorrentManager
{
    public function search($search, $page)
    {
        $videos =  array_merge($this->searchYTSam($search), $this->searchLegitTorrent($search), $this->searchArchiveOrg($search));

        usort($videos, function($a, $b) use ($search){
            $val = 0;
            if ('title' === $search->getSortBy())
            {
                $val = strcmp($a->getTitle(), $b->getTitle());
            }
            if ('year' === $search->getSortBy())
            {
                $valA = $a->getProductionDate() ? $a->getProductionDate()->getTimestamp() : 0;
                $valB = $b->getProductionDate() ? $b->getProductionDate()->getTimestamp() : 0;
                $val = $valA - $valB;
            }
            if ('rating' === $search->getSortBy())
            {
                $val = $a->getNotation() - $b->getNotation();
            }
            if ('peers' === $search->getSortBy())
            {
                $val = $a->getNbSeeder() - $b->getNbSeeder();
            }
            if ('seeds' === $search->getSortBy())
            {
                $val = $a->getNbSeeder() - $b->getNbSeeder();
            }
            if ('download_count' === $search->getSortBy())
            {
                $val = $a->getNbLeecher() - $b->getNbLeecher();
            }
            if ('like_count' === $search->getSortBy())
            {
                $val = $a->getNotation() - $b->getNotation();
            }
            if ('date_added' === $search->getSortBy())
            {
                $val = $a->getProductionDate() - $b->getProductionDate();
            }
            
            if ('desc' == $search->getOrderBy())
            {
                $val = 0 - $val;
            }
            return $val;
        });

        $i = 0;
        $newVideos = [];
        $start = $page * 10;
        $stop = $start + 10;
        foreach ($videos as $video) {
            if ($i >= $start && $i < $stop)
            {
                $good = true;
                if(NULL != $search->getProductionYearMin())
                {
                    if ($video->getProductionDate()->format('Y') < $search->getProductionYearMin())
                        $good = false;
                }
                if(NULL != $search->getProductionYearMax())
                {
                    if ($video->getProductionDate()->format('Y') > $search->getProductionYearMax())
                        $good = false;
                }
                if($good)
                    $newVideos[] = $video;
            }
            $i++;
        }



        return $newVideos;
    }

    public function searchLegitTorrent($search)
    {
        $url = 'http://www.legittorrents.info/index.php?search='.urlencode($search->getSearch()).'&page=torrents&category=1&active=1';

        $html = file_get_contents($url);

        $crawler = new Crawler($html);

        $crawler = $crawler->filterXPath('//td[@valign=\'middle\']/a');

        // We get the names and urls
        $results = [];
        foreach ($crawler as $domElement) {
            if (is_null($domElement))
                continue;
            $results[] = [
                'url' => $domElement->getAttribute('href'),
                'name' => $domElement->nodeValue,
            ];
        }

        $videos = [];
        // We get the rest of the stuff.
        foreach ($results as $value) {
            $video = new Video();
            $video->setTitle($value['name'])
            ->setSource(2);
            

            $html = file_get_contents('http://www.legittorrents.info/'.$value['url']);
            
            $crawler = new Crawler($html);
            $crawler = $crawler->filterXPath('//tr');

            foreach ($crawler as $domElement) {
                if (is_null($domElement))
                {
                    //var_dump('is_null');
                    continue;
                }
                if ($domElement->childNodes[0]->nodeValue == 'Description')
                {
                    $video->setDescription($domElement->childNodes[2]->nodeValue);
                }
                else if ($domElement->childNodes[0]->nodeValue == 'AddDate')
                {
                    // Todo
                    // $value['date'] = $domElement->childNodes[2]->nodeValue;
                }
                else if ($domElement->childNodes[0]->nodeValue == 'Info Hash')
                {
                    $video->setBtih($domElement->childNodes[2]->nodeValue);
                } 
                
            }
            $video->setTorrentUrl('http://www.legittorrents.info/download.php?id='.$video->getBtih().'&f=osef.torrent');
            $video->setDownloadable(false)
                ->setProcessStarted(false)
                ;
            $videos[] = $video;
        }
        return $videos;
    }

    public function searchArchiveOrg($search)
    {
        $url = 'https://archive.org/advancedsearch.php?q=(movies)+AND+title%3A('.urlencode($search->getSearch()).')+AND+mediatype%3A(movies)&+AND+date%3A%5B'.urlencode($search->getProductionYearMin()).'+TO+'.urlencode($search->getProductionYearMax()).'%5D&fl%5B%5D=avg_rating&fl%5B%5D=backup_location&fl%5B%5D=btih&fl%5B%5D=call_number&fl%5B%5D=collection&fl%5B%5D=contributor&fl%5B%5D=coverage&fl%5B%5D=creator&fl%5B%5D=date&fl%5B%5D=description&fl%5B%5D=downloads&fl%5B%5D=external-identifier&fl%5B%5D=foldoutcount&fl%5B%5D=format&fl%5B%5D=genre&fl%5B%5D=headerImage&fl%5B%5D=identifier&fl%5B%5D=imagecount&fl%5B%5D=indexflag&fl%5B%5D=item_size&fl%5B%5D=language&fl%5B%5D=licenseurl&fl%5B%5D=mediatype&fl%5B%5D=members&fl%5B%5D=month&fl%5B%5D=name&fl%5B%5D=noindex&fl%5B%5D=num_reviews&fl%5B%5D=oai_updatedate&fl%5B%5D=publicdate&fl%5B%5D=publisher&fl%5B%5D=related-external-id&fl%5B%5D=reviewdate&fl%5B%5D=rights&fl%5B%5D=scanningcentre&fl%5B%5D=source&fl%5B%5D=stripped_tags&fl%5B%5D=subject&fl%5B%5D=title&fl%5B%5D=type&fl%5B%5D=volume&fl%5B%5D=week&fl%5B%5D=year&sort%5B%5D=titleSorter+'.urlencode($search->getOrderBy()).'&sort%5B%5D=&sort%5B%5D=&rows=100&page=1&output=json&save=yes#raw';



        $datas = json_decode(file_get_contents($url), true);
        // Check if result is empty
        $datas = $datas['response']['docs'];
        //dump($datas); // a commenter apres
        // die;

        $videos = [];
        if ($datas === null)
            return $videos;
        foreach ($datas as $data) {
            if(empty($data['btih']))
                continue;

            $video = new Video();
            if (isset($data['description']) && is_array($data['description'])){
                $data['description'] = $data['description'][0];
            }
            $video
                ->setTitle($data['title'])
                ->setTorrentUrl('https://archive.org/download/'.$data['identifier'].'/'.$data['identifier'].'_archive.torrent')
                ->setDescription($data['description'] ?? '')
                ->setBtih($data['btih'])
                ->setSource(1)
                ->setDownloadable(false)
                ->setProcessStarted(false)
                ;
            $videos[] = $video;
        }    
        return $videos;
    }



    public function searchYTSam($search)
    {
        $url = 'https://yts.am/api/v2/list_movies.json?query_term='.urlencode($search->getSearch()).'&sort='.urlencode($search->getSortBy()).'&order_by='.urlencode($search->getOrderBy()).'&minimum_rating='.urlencode($search->getNotationMin()).'&genre='.urlencode($search->getGenre());
        $datas = json_decode(file_get_contents($url), true);

        if (!is_array($datas['data']))
            return [];
        if (!isset($datas['data']['movies']) || !is_array($datas['data']['movies']))
            return [];

        $datas = ($datas['data']['movies']); //problemme si pas de movies
        //dump($datas); // a commenter apes
        // die;
        $videos = [];

        foreach ($datas as $data) {
            $video = new Video();
            if (isset($data['description']) && is_array($data['description']))
            {
                $data['description'] = $data['description'][0];
            }
            if (isset($data['torrents']) && is_array($data['torrents']))
            {
                $data['url'] = $data['torrents'][0];
            }

            if($torrent = $this->searchYTSam_searchQuality($data['torrents'], '1080p'))
            {
                $video->setTorrentUrl($torrent['url']);
                $video->setBtih($torrent['hash']);
            }
            elseif ($torrent = $this->searchYTSam_searchQuality($data['torrents'], '720p'))
            {
                $video->setTorrentUrl($torrent['url']);
                $video->setBtih($torrent['hash']);
            }
            $video
                ->setTitle($data['title'])
                ->setDescription($data['description_full'] ?? '')
                ->setProductionDate(\DateTime::createFromFormat('Y-m-d H:i:s', $data['year'].'-01-01 00:00:00'))
                ->setDuration($data['runtime'] * 60)
                ->setPictureUrl($data['medium_cover_image'])
                ->setNotation($data['rating'])
                ->setSource(1)
                ->setDownloadable(false)
                ->setProcessStarted(false)
                ;
            $videos[] = $video;
        }
        //dump($video);
        return $videos;
    }

    public function searchYTSam_searchQuality($tab, $quality)
    {
        foreach ($tab as $line) {
            if($line['quality'] === $quality)
            {
                return $line;
            }
        }
        return null;
    }

}

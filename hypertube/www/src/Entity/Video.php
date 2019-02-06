<?php

namespace App\Entity;

use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity(repositoryClass="App\Repository\VideoRepository")
 */
class Video
{
    /**
     * @ORM\Column(type="string", length=255)
     */
    private $title;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $torrentUrl;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $nbDownload;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $nbSeeder;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $nbLeecher;

    /**
     * @ORM\Column(type="datetime", nullable=true)
     */
    private $productionDate;

    /**
     * @ORM\Column(type="string", length=255, nullable=true)
     */
    private $pictureUrl;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $notation;

    /**
     * @ORM\Column(type="datetime", nullable=true)
     */
    private $downloadStartedAt;

    /**
     * @ORM\Column(type="datetime", nullable=true)
     */
    private $downloadFinishAt;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $bytes;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $downloadBytesDone;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $nbSee;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $genre;

    /**
     * @ORM\Column(type="text", nullable=true)
     */
    private $description;

    /**
     * @ORM\Column(type="text", nullable=true)
     */
    private $casting;

    /**
     * @ORM\Column(type="integer", nullable=true)
     */
    private $duration;

    /**
     * @ORM\Column(type="datetime", nullable=true)
     */
    private $lastSeeAt;

    /**
     * @ORM\Id()
     * @ORM\Column(type="string", length=255, unique=true)
     */
    private $btih;

    /**
     * @ORM\Column(type="integer")
     */
    private $source;

    /**
     * @ORM\OneToMany(targetEntity="App\Entity\Comment", mappedBy="video", orphanRemoval=true)
     */
    private $comments;

     /**
     * @ORM\OneToMany(targetEntity="App\Entity\Subtitle", mappedBy="video", orphanRemoval=true)
     */
    private $subtitles;

    /**
     * @ORM\Column(type="boolean")
     */
    private $downloadable;


    /**
     * @ORM\Column(type="boolean")
     */
    private $processStarted;


    public function __construct()
    {
        $this->comments = new ArrayCollection();
        $this->subtitles = new ArrayCollection();
    }

    public function getTitle(): ?string
    {
        return $this->title;
    }

    public function setTitle(string $title): self
    {
        $this->title = $title;

        return $this;
    }

    public function getTorrentUrl(): ?string
    {
        return $this->torrentUrl;
    }

    public function setTorrentUrl(string $torrentUrl): self
    {
        $this->torrentUrl = $torrentUrl;

        return $this;
    }

    public function getNbDownload(): ?int
    {
        return $this->nbDownload;
    }

    public function setNbDownload(int $nbDownload): self
    {
        $this->nbDownload = $nbDownload;

        return $this;
    }

    public function getNbSeeder(): ?int
    {
        return $this->nbSeeder;
    }

    public function setNbSeeder(int $nbSeeder): self
    {
        $this->nbSeeder = $nbSeeder;

        return $this;
    }

    public function getProductionDate(): ?\DateTimeInterface
    {
        return $this->productionDate;
    }

    public function setProductionDate(?\DateTimeInterface $productionDate): self
    {
        $this->productionDate = $productionDate;

        return $this;
    }

    public function getPictureUrl(): ?string
    {
        return $this->pictureUrl;
    }

    public function setPictureUrl(?string $pictureUrl): self
    {
        $this->pictureUrl = $pictureUrl;

        return $this;
    }

    public function getNotation(): ?int
    {
        return $this->notation;
    }

    public function setNotation(?int $notation): self
    {
        $this->notation = $notation;

        return $this;
    }

    public function getDownloadStartedAt(): ?\DateTimeInterface
    {
        return $this->downloadStartedAt;
    }

    public function setDownloadStartedAt(?\DateTimeInterface $downloadStartedAt): self
    {
        $this->downloadStartedAt = $downloadStartedAt;

        return $this;
    }

    public function getDownloadFinishAt(): ?\DateTimeInterface
    {
        return $this->downloadFinishAt;
    }

    public function setDownloadFinishAt(?\DateTimeInterface $downloadFinishAt): self
    {
        $this->downloadFinishAt = $downloadFinishAt;

        return $this;
    }

    public function getDownloadBytesDone(): ?int
    {
        return $this->downloadBytesDone;
    }

    public function setDownloadBytesDone(?int $downloadBytesDone): self
    {
        $this->downloadBytesDone = $downloadBytesDone;

        return $this;
    }

    public function getNbSee(): ?int
    {
        return $this->nbSee;
    }

    public function setNbSee(int $nbSee): self
    {
        $this->nbSee = $nbSee;

        return $this;
    }

    public function getGenre(): ?int
    {
        return $this->genre;
    }

    public function setGenre(?int $genre): self
    {
        $this->genre = $genre;

        return $this;
    }

    public function getDescription(): ?string
    {
        return $this->description;
    }

    public function setDescription(?string $description): self
    {
        $this->description = $description;

        return $this;
    }

    public function getCasting(): ?string
    {
        return $this->casting;
    }

    public function setCasting(?string $casting): self
    {
        $this->casting = $casting;

        return $this;
    }

    public function getDuration(): ?int
    {
        return $this->duration;
    }

    public function setDuration(?int $duration): self
    {
        $this->duration = $duration;

        return $this;
    }

    public function getLastSeeAt(): ?\DateTimeInterface
    {
        return $this->lastSeeAt;
    }

    public function setLastSeeAt(?\DateTimeInterface $lastSeeAt): self
    {
        $this->lastSeeAt = $lastSeeAt;

        return $this;
    }

    public function getBtih(): ?string
    {
        return $this->btih;
    }

    public function setBtih(string $btih): self
    {
        $this->btih = $btih;

        return $this;
    }

    public function getNbLeecher(): ?int
    {
        return $this->nbLeecher;
    }

    public function setNbLeecher(?int $nbLeecher): self
    {
        $this->nbLeecher = $nbLeecher;

        return $this;
    }

    public function getSource(): ?int
    {
        return $this->source;
    }

    public function setSource(int $source): self
    {
        $this->source = $source;

        return $this;
    }

    public function getMagnet()
    {
        $uri = 'magnet:?xt=urn:btih:'.$this->getBtih();
        if ($this->source == 1) // Archive.org
        {
            $uri .= '&tr=http%3a%2f%2fbt1.archive.org%3a6969%2fannounce&tr=http%3a%2f%2fbt2.archive.org%3a6969%2fannounce';
        }
        if ($this->source == 2) // Legittorrent
        {
            $uri .= '&tr=udp%3a%2f%2ftracker.coppersurfer.tk%3a6969&tr=udp%3a%2f%2ftracker.leechers-paradise.org%3a6969&tr=udp%3a%2f%2ftracker.openbittorrent.com%3a80&tr=udp%3a%2f%2fopen.demonii.com%3a1337';
        }
        return $uri;
    }

    /**
     * @return Collection|Comment[]
     */
    public function getComments(): Collection
    {
        return $this->comments;
    }

    public function addComment(Comment $comment): self
    {
        if (!$this->comments->contains($comment)) {
            $this->comments[] = $comment;
            $comment->setVideo($this);
        }

        return $this;
    }

    public function removeComment(Comment $comment): self
    {
        if ($this->comments->contains($comment)) {
            $this->comments->removeElement($comment);
            // set the owning side to null (unless already changed)
            if ($comment->getVideo() === $this) {
                $comment->setVideo(null);
            }
        }

        return $this;
    }

    public function getBytes(): ?int
    {
        return $this->bytes;
    }

    public function setBytes(?int $bytes): self
    {
        $this->bytes = $bytes;

        return $this;
    }

    public function getDownloadable()
    {
        return $this->downloadable;
    }

    public function setDownloadable($downloadable): self
    {
        $this->downloadable = $downloadable;

        return $this;
    }

    public function getProcessStarted()
    {
        return $this->processStarted;
    }

    public function setProcessStarted($processStarted): self
    {
        $this->processStarted = $processStarted;

        return $this;
    }

    /**
     * @return Collection|Subtitle[]
     */
    public function getSubtitles(): Collection
    {
        return $this->subtitles;
    }

    public function addSubtitle(Subtitle $subtitle): self
    {
        if (!$this->subtitles->contains($subtitle)) {
            $this->subtitles[] = $subtitle;
            $subtitle->setVideo($this);
        }

        return $this;
    }

    public function removeSubtitle(Subtitle $subtitle): self
    {
        if ($this->subtitles->contains($subtitle)) {
            $this->subtitles->removeElement($subtitle);
            // set the owning side to null (unless already changed)
            if ($subtitle->getVideo() === $this) {
                $subtitle->setVideo(null);
            }
        }

        return $this;
    }
}

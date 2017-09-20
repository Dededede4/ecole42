<?php

namespace Framework\Templating;

use Framework\Http\Request;
use Framework\Routing\Resolver;

class PhpEngine
{
    private $resolver;

    private $blocks = array();

    private $extended;

    public function __construct(Resolver $resolver, Request $request)
    {
        $this->resolver = $resolver;
        $this->request = $request;
    }

    public function path($routeName, $args = array())
    {
        return $this->resolver->generatePath($routeName, $this->request, $args);
    }

    public function render($path, array $vars = array())
    {
        ob_start();
        include(ROOTDIR.'/srcs/View/'.$path);
        $html = ob_get_contents();
        ob_end_clean();
        if ($this->extended)
        {
            $path = $this->extended;
            $this->extended = null;
            return $this->render($path);
        }
        return $html;
    }

    private function extends($file)
    {
        $this->extended = $file;
    }

    public function startBlock()
    {
        ob_start();
    }

    public function endBlock($name)
    {
        $this->blocks[$name] = ob_get_clean();
    }

    public function getBlock($name, $default = '')
    {
        return $this->blocks[$name] ?? $default;
    }
}
/*
 * <!-- templates/list.php -->
<?php $title = 'List of Posts' ?>

<?php ob_start() ?>
    <h1>List of Posts</h1>
    <ul>
        <?php foreach ($posts as $post): ?>
        <li>
            <a href="/show.php?id=<?= $post['id'] ?>">
                <?= $post['title'] ?>
            </a>
        </li>
        <?php endforeach ?>
    </ul>
<?php $content = ob_get_clean() ?>

<?php include 'layout.php' ?>
 */
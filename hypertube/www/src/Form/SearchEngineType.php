<?php

namespace App\Form;

use App\Entity\Search;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;

use Symfony\Component\Form\Extension\Core\Type\TextType;
use Symfony\Component\Form\Extension\Core\Type\NumberType;
use Symfony\Component\Form\Extension\Core\Type\ChoiceType;


class SearchEngineType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder
            ->add('seederMin', NumberType::class, ['required' => false,])
            ->add('seederMax', NumberType::class, ['required' => false,])
            ->add('search', TextType::class, ['required' => false,])
            ->add('productionYearMin', NumberType::class, ['required' => false,])
            ->add('productionYearMax', NumberType::class, ['required' => false,])
            ->add('notationMin', NumberType::class, ['required' => false,])
            ->add('notationMax', NumberType::class, ['required' => false,])
            ->add('genre', ChoiceType::class, ['required' => false,
                'choices'  => [
                    'Action' => 'Action',
                    'Adventure' => 'Adventure',
                    'Animation' => 'Animation',
                    'Biography' => 'Biography',
                    'Comedy' => 'Comedy',
                    'Crime' => 'Crime',
                    'Documentary' => 'Documentary',
                    'Drama' => 'Drama',
                    'Family' => 'Family',
                    'Fantasy' => 'Fantasy',
                    'Film Noir' => 'Film Noir',
                    'History' => 'History',
                    'Horror' => 'Horror',
                    'Music' => 'Music',
                    'Musical' => 'Musical',
                    'Mystery' => 'Mystery',
                    'Romance' => 'Romance',
                    'Sci-Fi' => 'Sci-Fi',
                    'Short' => 'Short',
                    'Sport' => 'Sport',
                    'Superhero' => 'Superhero',
                    'Thriller' => 'Thriller',
                    'War' => 'War',
                    'Western' => 'Western',
            ]])
            ->add('orderBy', ChoiceType::class, ['choices'  => ['desc' => 'desc', 'asc' => 'asc'], 'required' => false,])
            ->add('sortBy', ChoiceType::class, [
                'choices' => [
                    'title' => 'title',
                    'year' => 'year',
                    'rating' => 'rating',
                    'peers' => 'peers',
                    'seeds' => 'seeds',
                    'download_count' => 'download_count',
                    'like_count' => 'like_count',
                    'date_added' => 'date_added',
                ],
                'required' => false,])
        ;
    }

    public function configureOptions(OptionsResolver $resolver)
    {
        $resolver->setDefaults([
            'data_class' => Search::class,
        ]);
    }
}

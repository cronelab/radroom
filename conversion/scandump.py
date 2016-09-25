#!/usr/bin/env python3


## IMPORTS

import os.path
import argparse

import numpy as np
import nibabel as nib

from PIL import Image


## HELPERS

def get_parser():

    parser = argparse.ArgumentParser( description = "REMEMBER THE FIRST RULE" )

    parser.add_argument( 'infile', nargs = '+' )
    parser.add_argument( '-o', '--out', dest = 'outdir', default = '.' )

    return parser

def process_file( file_path,
                  output_dir,
                  output_format = 'png',
                  n_slices_u = None,
                  n_slices_v = None ):

    # Load scan data
    scan = nib.load( file_path )
    scan_data = scan.get_data()

    # Determine texture geometry
    if n_slices_u is None:
        n_slices_u = 16
    if n_slices_v is None:
        n_slices_v = 16

    # Allocate return value
    processed_data = np.zeros( ( scan_data.shape[0] * n_slices_u,
                                 scan_data.shape[1] * n_slices_v ) )

    slice_u = 0
    slice_v = 0
    for i in range( scan_data.shape[2] ):

        u_min = scan_data.shape[0] * slice_u
        u_max = u_min + scan_data.shape[0]
        v_min = scan_data.shape[1] * slice_v
        v_max = v_min + scan_data.shape[1]

        processed_data[u_min:u_max, v_min:v_max] = scan_data[:, :, i]

        slice_u = slice_u + 1
        if slice_u >= n_slices_u:
            slice_v = slice_v + 1
            slice_u = 0

        if slice_v >= n_slices_v:
            break

    # Rescale to [0, 255]
    processed_data = ( 255 / ( np.max( processed_data ) - np.min( processed_data ) ) ) * ( processed_data - np.min( processed_data ) )

    # Output texture image

    im = Image.fromarray( processed_data )
    im = im.convert( 'RGB' )

    file_name = os.path.splitext( os.path.splitext( os.path.split( file_path )[1] )[0] )[0]

    im.save( os.path.join( output_dir, '{0}.{1}'.format( file_name, output_format ) ) )


## MAIN

def main():
    
    args = get_parser().parse_args()

    for file_path in args.infile:
        print( 'Processing file: {0}'.format( file_path ) )
        process_file( file_path, args.outdir )

    return 0


if __name__ == '__main__':
    main()
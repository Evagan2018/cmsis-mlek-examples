/*---------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited (or its affiliates).
 * All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include CMSIS_device_header

#include "ethosu_driver.h"
#include "app_mem_regions.h"

#define MRAM_BASE APP_MRAM_HE_BASE
#define MRAM_SIZE APP_MRAM_HE_SIZE

typedef struct {
  uint32_t start_addr;  // Base address of a block
  uint32_t end_addr;    // End address of a block (inclusive)
} mem_block_t;

const mem_block_t non_cached_memory[] = {
  { 0x00000000, 0x01FFFFFF }, /* TCM */
  { 0x20000000, 0x21FFFFFF }, /* TCM */
  { MRAM_BASE, MRAM_BASE + MRAM_SIZE - 1 } /* MRAM */
};

/**
  \brief Check whether one memory region requires cache maintenance.
  \param[in] p      Pointer to the memory region start address.
  \param[in] bytes  Size of the memory region in bytes.
  \return           true if cache maintenance is required, false otherwise.
 */
static bool check_mem_region(const void *p, size_t bytes) {
  uint32_t mem_start = (uint32_t)(uintptr_t)p;
  uint32_t mem_end   = mem_start + bytes - 1U;
  uint32_t n_blocks  =
      sizeof(non_cached_memory) / sizeof(non_cached_memory[0]);

  for (uint32_t block = 0U; block < n_blocks; block++) {
    if ((mem_start >= non_cached_memory[block].start_addr) &&
        (mem_end <= non_cached_memory[block].end_addr)) {
      return false;
    }
  }

  return true;
}

/**
  \brief Check whether any memory region requires cache maintenance.
  \param[in] base_addr       Array containing the memory region base addresses.
  \param[in] base_addr_size  Array containing the size of each region in bytes.
  \param[in] num_base_addr   Number of entries in the address and size arrays.
  \return                    true if cache maintenance is required, false otherwise.
 */
static bool check_mem_regions(const uint64_t *base_addr,
                              const size_t *base_addr_size,
                              int num_base_addr) {
  if ((base_addr == NULL) || (base_addr_size == NULL)) {
    return true;
  }

  for (int index = 0; index < num_base_addr; index++) {
    const void *p = (const void *)(uintptr_t)base_addr[index];

    if (check_mem_region(p, base_addr_size[index])) {
      return true;
    }
  }

  return false;
}

/**
  \brief Clean the data cache for the supplied memory regions.
  \param[in] base_addr       Array containing the memory region base addresses.
  \param[in] base_addr_size  Array containing the size of each region in bytes.
  \param[in] num_base_addr   Number of entries in the address and size arrays.
 */
void ethosu_flush_dcache(const uint64_t *base_addr,
                         const size_t *base_addr_size,
                         int num_base_addr) {
  if (check_mem_regions(base_addr, base_addr_size, num_base_addr)) {
    /*
     * Clean the whole cache once because at least one supplied region
     * resides in cacheable memory.
     */
    SCB_CleanDCache();
  } else {
    __DSB();
  }
}

/**
  \brief Invalidate the data cache for the supplied memory regions.
  \param[in] base_addr       Array containing the memory region base addresses.
  \param[in] base_addr_size  Array containing the size of each region in bytes.
  \param[in] num_base_addr   Number of entries in the address and size arrays.
 */
void ethosu_invalidate_dcache(const uint64_t *base_addr,
                              const size_t *base_addr_size,
                              int num_base_addr) {
  if (check_mem_regions(base_addr, base_addr_size, num_base_addr)) {
    SCB_CleanInvalidateDCache();
  } else {
    __DSB();
  }
}
